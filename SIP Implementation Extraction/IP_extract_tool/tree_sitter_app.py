import tree_sitter_c as tspython
from tree_sitter import Language, Parser

from utils import record_range_content
from main_class import MacroExprInfo, SubFunctionInfo, FunMacroExprInfo
from utils import find_function_cursor, get_type_name, is_from_standard_library, find_c_file_path
C_LANGUAGE = Language(tspython.language())
parser = Parser(C_LANGUAGE)

def parse_source_file(code):
    """
    使用 tree-sitter 解析源文件并生成 AST。
    :param file_path: 源文件路径
    :return: 解析后的 AST
    """
    tree = parser.parse(bytes(code, "utf8"))
    return tree

def get_node_range(node):
    """
    获取节点的范围，返回0索引的起始行、起始列、结束行、结束列。

    :param node: Tree-sitter节点
    :return: (start_line, start_col, end_line, end_col)
    """
    start_point = node.start_point
    end_point = node.end_point
    return (start_point[0], start_point[1], end_point[0], end_point[1])


def classify_argument(arg_node, caller_code, tu_item_dict):
    """
    分类实参节点为 variable 或 function。
    :param arg_node: 实参节点。
    :param caller_code: 原始源代码字符串。
    :return: 类型（'variable' 或 'function'）和对应的源代码片段。
    """
    arg_range =get_node_range(arg_node)
    print(arg_range)
    code_snippet = record_range_content(caller_code, arg_range)
    print(code_snippet)
    
    # 如果node是函数调用表达式，而且不是宏调用
    if arg_node.type == 'call_expression':
        for key in tu_item_dict.keys():
            if arg_node.children[0].text.decode('utf-8') == key.split('@')[0]:
                return code_snippet, 'variable'
        return code_snippet, 'function'
    else:
        return code_snippet, 'variable'


def extract_arguments_with_types(tree_sitter_function_cursor, caller_code, tu_item_dict):
    """
    提取函数调用的所有实参节点及其类型。
    :param tree_sitter_function_cursor: 函数调用表达式的节点。
    :param caller_code: 表达式字符串。
    :return: 包含实参类型和源代码片段的列表。
    """
    args = []
    if tree_sitter_function_cursor.type == 'call_expression':
        argument_list_node = None
        for child in tree_sitter_function_cursor.children:
            if child.type == 'argument_list':
                print(f'\n\n函数{tree_sitter_function_cursor.text.decode("utf-8")}的参数列表是{child.text.decode("utf-8")}\n\n')
                argument_list_node = child
                break
        
        if argument_list_node:
            # 遍历参数列表中的所有子节点，跳过括号
            for arg_node in argument_list_node.named_children:
                if arg_node.type != ',' and arg_node.is_named:  # 过滤掉逗号分隔符
                    code_snippet, arg_type = classify_argument(arg_node, caller_code, tu_item_dict)
                    args.append((code_snippet, arg_type))


    return args


def create_var_mapping(libclang_function_cursor, tree_sitter_function_cursor, caller_code, tu_item_dict, macro_info = None):
    """
    创建形参到实参的映射
    :param libclang_function_cursor: 函数游标,通过libclang获取
    :param tree_sitter_function_cursor: 子函数游标,通过tree-sitter获取
    :param caller_code: 表达式代码,通过tree-sitter获取
    :return: 形参到实参的映射
    """
    var_mapping = {}
    params = [param.spelling for param in libclang_function_cursor.get_arguments()]

    # 将形参类型添加到macro_info中
    if macro_info:
        param_type = [get_type_name(param.type.spelling) for param in libclang_function_cursor.get_arguments()]
        for type in param_type:
            macro_info.include_type_set.add(type)

    args = extract_arguments_with_types(tree_sitter_function_cursor, caller_code, tu_item_dict)
    print(f'\n函数{tree_sitter_function_cursor.text.decode("utf-8")}的参数列表是{args}\n')
    for param, arg in zip(params, args):
            var_mapping[param] = {'arg': arg[0], 'type': arg[1]}

    return var_mapping



# def find_macros_in_function(caller_code, tu_item_dict, macro_expr_info_list):
#     """
#     找到函数中使用的宏。
#     :param caller_code: 函数的源代码字符串
#     :param tu_item_dict: 全局项字典，键为 {name}@{file_path}，值为其他信息
#     :return: 函数中使用的宏名称列表
#     """
#     # 解析函数代码为 AST
#     tree = parse_source_file(caller_code)
#     root_node = tree.root_node
#
#     def traverse(node, tu_item_dict, macro_expr_info_list):
#         if node.type == 'identifier':
#             macro_name = node.text.decode('utf-8')
#             for identifier in tu_item_dict:
#                 if identifier.split('@')[0] == macro_name:
#                     tu_item_dict[identifier]['flag'] = True
#
#                     # 使用 get_node_range 提取范围
#                     macro_range = get_node_range(node)
#                     macro_expr_info_list.append(MacroExprInfo(
#                         name=identifier,
#                         content_range=macro_range
#                     ))
#
#         for child in node.children:
#             traverse(child, tu_item_dict, macro_expr_info_list)
#
#     traverse(root_node, tu_item_dict, macro_expr_info_list)


def insert_before_identifier(code: str, fun_var_dict: dict):
    """
    在函数体内查找所有出现在指定结构中的参数，并在其前面插入 "pIp -> "。
    使用 Tree-sitter 进行语法树解析。
    """
    # 解析代码
    tree = parser.parse(bytes(code, 'utf8'))
    root_node = tree.root_node

    # 存储修改后的代码片段及其插入位置
    insertions = []

    def traverse(node):
        if node.type == 'identifier':
            identifier_bytes = bytes(code, 'utf8')[node.start_byte:node.end_byte]
            try:
                identifier_text = identifier_bytes.decode('utf8')
                if identifier_text in fun_var_dict:
                    # 记录需要插入的位置和内容
                    insertions.append((node.start_byte, b'pIp -> '))
            except UnicodeDecodeError as e:
                print(f"Warning: Failed to decode identifier at byte range [{node.start_byte}, {node.end_byte}): {e}")

        # 遍历子节点
        for child in node.children:
            traverse(child)

    # 查找所有函数体内的标识符
    for child in root_node.children:
        if child.type == 'function_definition':
            compound_statement = None
            for sub_child in child.children:
                if sub_child.type == 'compound_statement':
                    compound_statement = sub_child
                    break
            if compound_statement:
                traverse(compound_statement)

    # 对插入操作进行排序（从后向前插入以避免影响后续插入点的位置）
    insertions.sort(reverse=True)

    # 执行插入操作
    modified_code = code.encode('utf8')
    for pos, insertion in insertions:
        modified_code = modified_code[:pos] + insertion + modified_code[pos:]

    return modified_code.decode('utf8')


def extract_macro_def_code(tu_macro_dict, file_code):
    """
    使用 Tree-sitter 提取宏定义中的宏名称和宏体。
    """

    # 解析代码
    tree = parser.parse(bytes(file_code, 'utf8'))
    root_node = tree.root_node


    def traverse(node):
        if node.type == 'preproc_def' or node.type == 'preproc_function_def':
            # 获取宏定义节点的所有子节点
            macro_name = None
            body = None

            for child in node.children:
                if child.type == 'identifier':
                    macro_name = child.text.decode('utf8')
                elif child.type == 'preproc_arg':
                    body = child.text.decode('utf8').strip()
            # # 如果没有找到body,再字典中删掉该宏
            # if not body:
            #     for identifier in tu_macro_dict:
            #         if identifier.split('@')[0] == macro_name:
            #             del tu_macro_dict[identifier]
            for identifier in tu_macro_dict:
                if identifier.split('@')[0] == macro_name:
                    tu_macro_dict[identifier].def_code = body
                    print(f'{macro_name} {body}')

        # 递归遍历所有子节点
        for child in node.children:
            traverse(child)

    traverse(root_node)


def extract_function_name(function_node):
    for child in function_node.children:
        if child.type == 'identifier':
            return child.text.decode('utf-8')



def build_sub_function_info_list(upper_function_cursor, root_dir, tu_dict, tu_item_dict, caller_code, unparsed_fun_set,
                                 macro_info=None):
    """
    构建子函数信息列表,同时将函数中含有的宏,全局变量添加到macro_info。
    """
    sub_function_info_list = []
    print(f'当前处理的子函数的主函数体为{upper_function_cursor.text.decode("utf-8")}')
    def traverse(cursor, is_fun = False):

        # 如果到达了空节点,或已经找到了函数,停止遍历
        if not cursor or is_fun:
            return

        #有可能是含参宏或是函数
        if cursor.type == 'call_expression':
            expr_name = extract_function_name(cursor)

            if expr_name:
                # 检查是否是含参宏
                # 假设是函数
                is_fun = True
                for identifier in tu_item_dict:
                    if identifier.split('@')[0] == expr_name:
                        if macro_info:
                            macro_info.include_macro_set.add(identifier)
                        #如果是宏,则is_fun重新置False
                        is_fun = False

            if is_fun:
                # 否则是函数
                sub_fun_name = extract_function_name(cursor)



                sub_fun_range = [cursor.start_point[0], cursor.start_point[1], cursor.end_point[0], cursor.end_point[1]]

                file_path = find_c_file_path(root_dir, sub_fun_name, tu_dict)

                #当没找到,有可能函数是局部定义的
                if file_path:

                    # 因为caller只会继续处理callee,对于sub_fun,将其加入unparsed_fun_set
                    sub_fun_body = cursor.text.decode('utf-8')
                    unparsed_fun_set.add(sub_fun_name)
                    print(f'function_name:{sub_fun_name}   file_path:{file_path}    root_dir:{root_dir}')
                    tu = tu_dict[file_path]
                    function_cursor = find_function_cursor(tu, sub_fun_name, is_definition=False)

                    # print(caller_code)


                    # 创建形参到实参的映射
                    var_mapping = create_var_mapping(function_cursor, cursor, caller_code, tu_item_dict, macro_info)

                    # 构造sub_function_info_list
                    sub_sub_function_info_list = build_sub_function_info_list(cursor, root_dir, tu, tu_item_dict,
                                                                              macro_info, unparsed_fun_set)

                    sub_function_info_list.append(SubFunctionInfo(
                        name=sub_fun_name,
                        body=sub_fun_body,
                        var_mapping=var_mapping,
                        content_range = sub_fun_range,
                        sub_function_info_list=sub_sub_function_info_list
                    ))

        # 遍历主函数的子节点
        for child in cursor.children:
            traverse(child)

    #遍历主函数的子节点
    for child in upper_function_cursor.children:
        traverse(child)

    return sub_function_info_list

def macro_item_update(tu, root_dir, tu_item_dict, macro_info, tu_var_dict, unparsed_fun_set):
    """
    使用 Tree-sitter 解析宏定义并提取宏中所有的宏,类型,全局变量和使用的函数
    """
    # 解析宏定义
    # 如果是空宏,跳过
    if not macro_info.def_code:
        return

    def_code = macro_info.def_code + ';'
    tree = parser.parse(bytes(def_code, 'utf8'))
    root_node = tree.root_node

    macro_expr_info_list = []

    def traverse(cursor,is_fun = False):

        # 如果到达了空节点,或已经找到了函数,停止遍历
        if not cursor or is_fun:
            return

        # 有可能是含参宏或是函数
        if cursor.type == 'call_expression':
            expr_name = extract_function_name(cursor)
            print(macro_info.file_path)
            print(f'{macro_info.macro_cursor.spelling} {def_code}')
            print(expr_name)
            if expr_name:
                # 检查是否是含参宏
                # 假设是函数
                is_fun = True
                for identifier in tu_item_dict:
                    if expr_name == identifier.split('@')[0]:
                        macro_info.include_macro_set.add(identifier)
                        # 如果是宏,则is_fun重新置False
                        is_fun = False

                if is_fun:
                    # 否则是函数
                    sub_fun_name = expr_name

                    sub_fun_body = cursor.text.decode('utf-8')

                    sub_fun_range = [cursor.start_point[0], cursor.start_point[1], cursor.end_point[0],
                                     cursor.end_point[1]]


                    function_cursor = find_function_cursor(tu, sub_fun_name, is_definition=False)

                    if function_cursor and not is_from_standard_library(function_cursor):

                        # 构造var_mapping
                        var_mapping = create_var_mapping(function_cursor, cursor, sub_fun_body, tu_item_dict, macro_info)

                        # 构造sub_function_info_list
                        sub_function_info_list = build_sub_function_info_list(cursor, root_dir, tu, tu_item_dict,
                                                                              macro_info, unparsed_fun_set)

                        macro_expr_info_list.append(MacroExprInfo(
                            name=sub_fun_name,
                            body=sub_fun_body,
                            origin_content_range=sub_fun_range,
                            var_mapping=var_mapping,
                            sub_function_info_list=sub_function_info_list
                        ))


        elif cursor.type == 'identifier':  # 可能是宏或者全局变量
            node_name = cursor.text.decode('utf-8')
            for identifier in tu_item_dict:
                # 检查是否是宏
                if tu_item_dict[identifier]['kind'] == 'macro' and node_name == identifier.split('@')[0]:
                    macro_info.include_macro_set.add(identifier)

                # 检查是否是全局变量
                elif tu_item_dict[identifier]['kind'] == 'global' and identifier == node_name:
                    macro_info.include_global_set.add(identifier)
                    if identifier in tu_var_dict:
                        macro_info.include_type_set.add(tu_var_dict[identifier]['kind'])

        # 检查是否是类型
        elif cursor.type == 'primitive_type' or cursor.type == 'type_identifier ':
            macro_info.include_type_set.add(cursor.text.decode('utf-8'))
            for child in cursor.children:
                traverse(child)

        #此时后续会根据is_fun来判断是否终止循环
        for child in cursor.children:
            traverse(child,is_fun)


    for child in root_node.children:
        traverse(child)

    macro_info.macro_expr_info_list = macro_expr_info_list


def extract_function_macros(function_code, root_dir, tu_dict, tu_item_dict, unparsed_fun_set):
    """
    使用 Tree-sitter 提取函数中的所有宏调用，并将带参宏的信息添加到 macro_expr_info_list。
    """

    # 解析代码
    tree = parser.parse(bytes(function_code, 'utf8'))
    root_node = tree.root_node

    fun_macro_expr_info_list = []

    def traverse(node, fun_macro_expr = False):

        if fun_macro_expr:
            return
        if node.type == 'identifier':
            macro_name = node.text.decode('utf8')
            for identifier in tu_item_dict:
                if tu_item_dict[identifier]['kind'] == 'macro' and identifier.split('@')[0] == macro_name:
                    print(f"找到了macro:{identifier}")
                    tu_item_dict[identifier]['flag'] = True
                    parent = node.parent
                    if parent and parent.type == 'call_expression':
                        print(f"找到了fun_macro_expr:{macro_name}")
                        fun_macro_expr = True

                        expr_body = parent.text.decode('utf8')
                        # 0索引
                        expr_range = get_node_range(parent)  # 这里是对函数的相对范围

                        sub_function_info_list = (
                            build_sub_function_info_list(parent, root_dir, tu_dict, tu_item_dict, function_code, unparsed_fun_set))

                        fun_macro_expr_info_list.append(FunMacroExprInfo(
                            name=macro_name,
                            body=expr_body,
                            content_range=expr_range,
                            sub_function_info_list=sub_function_info_list
                        ))
        # 递归遍历所有子节点
        for child in node.children:
            traverse(child, fun_macro_expr)


    for child in root_node.children:
        traverse(child)
    
    return fun_macro_expr_info_list


def callee_info_update(caller_code, tu_dict, tu_item_dict, callee_info, unparsed_fun_set, root_dir):
    """
    更新callee的var_mapping和sub_function_info_list
    :param caller_code: 函数体代码
    :param tu_dict: 翻译单元
    :param tu_item_dict: 翻译单元字典
    :param callee_info: 被调用函数的CalleeInfo对象
    """
    # 解析代码
    libclang_del_cursor = callee_info.def_cursor
    tree = parse_source_file(caller_code)
    root_node = tree.root_node
    
    def traverse(node):
        if node.type == 'call_expression':
            sub_function_range = get_node_range(node)
            if sub_function_range == callee_info.content_range:
                # expression_code = node.text.decode('utf-8')
                # 创建形参到实参的映射  
                callee_info.var_mapping = create_var_mapping(libclang_del_cursor, node, caller_code, tu_item_dict)
                callee_info.sub_function_info_list = build_sub_function_info_list(node, root_dir, tu_dict, tu_item_dict,
                                                                                  caller_code, unparsed_fun_set)

            
        for child in node.children:
            traverse(child) 
            
    return traverse(root_node)

