import clang.cindex
from extract_all import parse_file
from parse_callee import callees_info_init
from utils import create_tu, get_type_name, find_function_cursor, record_content_range, is_from_standard_library, get_item_identifier, read_file_content, record_range_content
import re
from tree_sitter_app import  extract_function_macros


def collect_relevant_headers(function_cursor):
    """记录所有在函数中使用的非标准库头文件"""
    relevant_header_set = set()

    def traverse(cursor):
        if cursor.location.file:
            if not is_from_standard_library(cursor):
                file_path = cursor.location.file.name
                relevant_header_set.add(file_path)

        for child in cursor.get_children():
            traverse(child)

    traverse(function_cursor)

    return relevant_header_set


def collect_global_in_func(node, tu_item_dict):
    """
    收集目标函数中所有在 tu_item_dict 中出现的全局变量
    """

    def visit(cursor):
        # 检查当前节点是否是全局变量的引用
        if cursor.kind == clang.cindex.CursorKind.DECL_REF_EXPR:
            referenced_cursor = cursor.referenced
            if referenced_cursor and referenced_cursor.kind == clang.cindex.CursorKind.VAR_DECL:
                var_name = referenced_cursor.spelling
                if var_name in tu_item_dict:
                    tu_item_dict[var_name]['flag'] = True

        # 递归遍历子节点
        for child in cursor.get_children():
            visit(child)

    visit(node)


# def collect_and_mark_macro():
#     """收集目标函数所有的macro"""



def collect_and_mark_types(function_cursor, tu_item_dict, tu_type_dict):
    """
    收集目标函数中出现的所有类型，并将tu_item_dict中相应类型的flag置为True。
    
    :param function_cursor: 目标函数的Cursor
    :param tu_item_dict: 全局项目字典
    :param tu_type_dict: 全局类型字典
    """
    types_used = set()  # 存储在函数中使用的类型

    def types_used_update(cursor):
        type_name = get_type_name(cursor.type.spelling)
        types_used.add(type_name)





    def traverse(node):
        # 收集函数签名中的参数类型
        if not is_from_standard_library(node):
            if node.kind == clang.cindex.CursorKind.FUNCTION_DECL:
                for child in node.get_children():
                    if child.kind == clang.cindex.CursorKind.PARM_DECL:
                        types_used_update(child)

            # 收集函数调用中的参数类型
            elif node.kind == clang.cindex.CursorKind.CALL_EXPR:
                for arg in node.get_arguments():
                    types_used_update(arg)

            # 收集变量引用的类型（包括全局变量）
            elif node.kind == clang.cindex.CursorKind.DECL_REF_EXPR:
                types_used_update(node)

            # 收集局部变量声明中的类型
            elif node.kind == clang.cindex.CursorKind.VAR_DECL:
                types_used_update(node)

            # 收集结构体成员引用中的类型
            elif node.kind == clang.cindex.CursorKind.MEMBER_REF_EXPR:
                types_used_update(node)

        # 递归处理子节点
        for child in node.get_children():
            traverse(child)

    # 遍历函数体，收集所有类型
    traverse(function_cursor)


    # 递归查找tu_type_dict中的相关类型
    def update_related_types(type_name):
        if type_name in tu_type_dict:
            type_info = tu_type_dict[type_name]
            for related_type in type_info.include_type_set:
                if related_type in tu_item_dict and not tu_item_dict[related_type]['flag']:
                    tu_item_dict[related_type]['flag'] = True
                    # 递归查找相关类型
                    update_related_types(related_type)

    print(f'\ntypes_used:{types_used}\n')
    # 更新tu_item_dict中的flag
    for identifier in tu_item_dict:
        if identifier.split('@')[0] in types_used and not tu_item_dict[identifier]['flag']:
            tu_item_dict[identifier]['flag'] = True
            update_related_types(identifier)



def is_standard_library_function(callee_cursor):
    """
    判断被调用函数是否来自标准库。

    :param callee_cursor: 被调用函数的 Cursor
    :return: 如果是标准库函数，返回 True；否则返回 False
    """
    if not callee_cursor or not callee_cursor.location.file:
        return False

    # 获取函数定义所在的文件路径
    file_path = callee_cursor.location.file.name.lower()

    # 检查文件路径是否包含标准库头文件路径
    standard_library_headers = [
        'stdio.h', 'stdlib.h', 'string.h', 'math.h', 'time.h', 'errno.h',
        'ctype.h', 'locale.h', 'setjmp.h', 'signal.h', 'stdarg.h', 'stddef.h',
        'stdint.h', 'inttypes.h', 'iso646.h', 'limits.h', 'float.h', 'complex.h',
        'fenv.h', 'tgmath.h', 'wchar.h', 'wctype.h', 'assert.h', 'stdalign.h',
        'stdatomic.h', 'stdbool.h', 'stdnoreturn.h', 'threads.h', 'uchar.h'
    ]

    # 检查文件路径是否以常见的标准库路径开头
    standard_library_paths = [
        '/usr/include/', '/usr/local/include/',
        '/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/'
    ]

    # 检查文件路径是否包含标准库头文件
    if any(header in file_path for header in standard_library_headers):
        return True

    # 检查文件路径是否以标准库路径开头
    if any(file_path.startswith(path) for path in standard_library_paths):
        return True

    return False


def analyze_return_stmts(function_code):
    """
    直接从函数源代码中查找所有return语句的位置
    
    :param function_code: 函数的源代码字符串
    :return: 包含所有return语句范围的列表
    """
    ret_range_list = []
    lines = function_code.splitlines()
    
    # 正则表达式匹配return语句，考虑前后可能有空格
    # 不匹配注释中的return
    pattern = r'^\s*return\s+.*?;|^\s*return\s*;'
    
    for line_idx, line in enumerate(lines):
        # 跳过注释行
        if re.match(r'^\s*//', line) or re.match(r'^\s*/\*', line):
            continue
            
        # 检查行中是否有注释，如果有，在注释前查找return
        comment_start = line.find('//')
        if comment_start != -1:
            line_to_check = line[:comment_start]
        else:
            line_to_check = line
            
        # 查找return语句
        match = re.search(pattern, line_to_check)
        if match:
            start_col = match.start()
            end_col = match.end()
            
            # 记录return语句的范围 [start_line, start_col, end_line, end_col]
            ret_range_list.append([line_idx, start_col, line_idx, end_col])
    
    return ret_range_list


def print_decl_stmt(function_cursor):
    """打印所有的decl_stmt节点并输出相应的代码"""
    function_start_line = function_cursor.extent.start.line
    
    print("\n=== DECL_STMT 节点信息 ===\n")
    
    # 使用迭代方法遍历所有节点
    def traverse_iterative():
        stack = [function_cursor]
        visited = set()
        
        while stack:
            cursor = stack.pop()
            
            # 避免重复处理同一个节点
            cursor_id = str(cursor.hash)
            if cursor_id in visited:
                continue
            visited.add(cursor_id)
            
            # 检查是否是声明语句
            if cursor.kind == clang.cindex.CursorKind.VAR_DECL:
                try:
                    # 获取节点范围

                    range_info = record_content_range(cursor)
                    
                    # 获取源代码
                    file_path = cursor.location.file.name
                    with open(file_path, 'r') as f:
                        file_content = f.read()
                    
                    code_snippet = record_range_content(file_content, range_info)
                    
                    # 打印信息
                    print(f"位置: 第 {range_info[0]+1} 行, 第 {range_info[1]+1} 列 到 第 {range_info[2]+1} 行, 第 {range_info[3]+1} 列")
                    print("代码片段:")
                    print("-" * 40)
                    print(code_snippet)
                    print("-" * 40)
                    
                    # 打印子节点信息
                    print("变量声明:")
                    for child in cursor.get_children():
                        if child.kind == clang.cindex.CursorKind.VAR_DECL:
                            print(f"  - 名称: {child.spelling}")
                            print(f"    类型: {child.type.spelling}")
                            
                            # 检查是否有初始化表达式
                            init_expr = None
                            for init_child in child.get_children():
                                init_expr = init_child
                                break
                            
                            if init_expr:
                                init_tokens = [token.spelling for token in init_expr.get_tokens()]
                                init_str = ' '.join(init_tokens)
                                print(f"    初始值: {init_str}")
                    
                    print("\n")
                except Exception as e:
                    print(f"处理 DECL_STMT 时出错: {e}")
            
            # 将子节点添加到栈中
            for child in cursor.get_children():
                stack.append(child)
    
    # 执行迭代遍历
    traverse_iterative()
    
    print("=== DECL_STMT 节点信息结束 ===\n")


def parse_function(root_dir, file_path, function_name, tu, file_cache, tu_dict, tu_item_dict, tu_type_dict,
                   function_info_dict):

    unparsed_fun_set = set()

    print(f'caller_name: {function_name}   file_path: {file_path}')
    function_cursor = find_function_cursor(tu, function_name)

    if(function_name == 'luaM_saferealloc_'):
        print(function_name)
    file_code = read_file_content(file_path, file_cache)

    content_range = record_content_range(function_cursor)


    # print(content_range)

    function_code = record_range_content(file_code, content_range)

    # print(caller_code)

    relevant_header_set = collect_relevant_headers(function_cursor)  # 记录所有与该函数相关的非标准库头文件

    collect_and_mark_types(function_cursor, tu_item_dict, tu_type_dict)  # 直接使用tu_item_dict更新类型标志

    print(function_code)
    print(file_path)
    macro_expr_info_list = extract_function_macros(function_code, root_dir, tu_dict, tu_item_dict,
                                                   unparsed_fun_set)  # 标记所有的函数中的宏并提取函数中所有含参宏
    print(f'macro_expr_info_list:{macro_expr_info_list}')
    callee_info_list = callees_info_init(root_dir, tu_dict, function_cursor, file_cache, tu_item_dict,
                                         function_info_dict,
                                         unparsed_fun_set)  # 创建callee的列表,记录他们的name,在原.c文件中的范围,其形参和caller实参的对应和sub_function_info_list

    func_type = function_cursor.result_type.spelling  # 提取函数的类型

    ret_range_list = analyze_return_stmts(function_code)  # 分析return语句

    # refine tu_item_dict
    fun_item_dict = {}
    print(f'\ntu_item_dict:{tu_item_dict}\n')
    for identifier in tu_item_dict:
        if tu_item_dict[identifier]['flag'] == True:
            fun_item_dict[identifier] = tu_item_dict[identifier]['kind']


    # 打印函数信息
    print_function_info(fun_item_dict, relevant_header_set, content_range, function_code, callee_info_list, func_type, ret_range_list, macro_expr_info_list)

    # print_decl_stmt(function_cursor)

    return (relevant_header_set, content_range, function_code,
            fun_item_dict, macro_expr_info_list, callee_info_list,
            function_cursor, func_type, ret_range_list, unparsed_fun_set)


def print_function_info(fun_item_dict, relevant_header_set, content_range, function_code, callee_info_list, func_type, ret_range_list, macro_expr_info_list):
    """
    打印函数信息，包括全局项目字典、相关头文件、函数代码、被调用信息、返回类型、返回语句范围和宏表达式信息。

    :param fun_item_dict: 函数项目字典
    :param relevant_header_set: 相关头文件集合
    :param content_range: 函数的内容范围
    :param function_code: 函数的源代码
    :param callee_info_list: 被调用信息列表
    :param func_type: 函数返回类型
    :param ret_range_list: 返回语句范围列表
    :param macro_expr_info_list: 函数中的宏表达式信息列表
    """
    print("=== 函数信息 ===")
    
    # 打印函数项目字典
    print("函数项目字典:")
    for identifier, kind in fun_item_dict.items():
        print(f"  - {kind.capitalize()}: {identifier}")

    # 打印相关头文件
    print("\n相关头文件:")
    for header in relevant_header_set:
        print(f"  - {header}")

    # 打印内容范围
    print(f"\n内容范围: {content_range}")

    # 打印函数代码
    print("\n函数源代码:")
    print(function_code)

    # 打印返回类型
    print(f"\n返回类型: {func_type}")

    # 打印返回语句范围
    print("\n返回语句范围:")
    for ret_range in ret_range_list:
        print(f"  - 行: {ret_range[0]}, 列: {ret_range[1]} 到 行: {ret_range[2]}, 列: {ret_range[3]}, 代码:{record_range_content(function_code, ret_range)}")

    # 打印被调用信息
    print("\n被调用信息:")
    for callee in callee_info_list:
        print(f"  - 被调用函数: {callee.name}, 文件: {callee.file_path}, 范围: {callee.content_range}, 代码: {record_range_content(function_code, callee.content_range)}")
        for param in callee.var_mapping:
            print(f"    - 形参: {param}, 实参: {callee.var_mapping[param]['arg']}")
        for sub_func in callee.sub_function_info_list:
            print(f"    - 子函数名称: {sub_func.name}, 参数映射: {sub_func.var_mapping}")
    print("\n函数内含参宏信息:")
    for fun_macro_expr in macro_expr_info_list:
        print(f"    - 被调用含参宏: {fun_macro_expr.name}, 代码: {fun_macro_expr.body}, 范围:{fun_macro_expr.content_range}")
        for sub_function_info in fun_macro_expr.sub_function_info_list:
            print(f"  - 子函数名称: {sub_function_info.name}, 原始范围: {sub_function_info.content_range}, 代码: {record_range_content(function_code, sub_function_info.content_range)}")



if __name__ == "__main__":

    # 缓存已读取的文件内容
    # file_path = '../Input/SAMCode_V1.01/g4eapp.c'
    # root_dir = '../Input/SAMCode_V1.01'
    # function_name = 'DSSDataGet'
    # function_name = 'GyroStateGet'


    # file_path = '../Input/test16/test.c'
    # root_dir = '../Input/test16'
    # function_name = 'main'
    # bc_file_name = 'myproject'


    # file_path = '../Input/test16/test.c'
    # root_dir = '../Input/test16'
    # function_name = 'main'
    # bc_file_name = 'myproject'

    # file_path = '../Input/lua/lgc.c'
    # root_dir = '../Input/lua'
    # function_name = 'sweeplist'
    # bc_file_name = 'lua'  # debug:当顶层出现函数调用,此时上下文为none,会将none传回

    # file_path = '../Input/lua/lgc.c'
    # root_dir = '../Input/lua'
    # function_name = 'freeobj'
    # bc_file_name = 'lua'  # debug:当顶层出现函数调用,此时上下文为none,会将none传回


    # file_path = '../Input/lua/lmem.c'
    # root_dir = '../Input/lua'
    # function_name = 'luaM_saferealloc_'
    # bc_file_name = 'lua'  # debug:当顶层出现函数调用,此时上下文为none,会将none传回
    #
    file_path = '../Input/lua/ldo.c'
    root_dir = '../Input/lua'
    function_name = 'luaD_seterrorobj'
    bc_file_name = 'lua'



    tu_dict = {}  # tu缓存
    file_cache = {}         #文件代码缓存
    function_info_dict = {}
    tu = create_tu(file_path, tu_dict)
    global_type_dict = {}
    global_macro_dict = {}
    global_var_dict = {}


    # 分析文件中的枚举类型及其使用情况
    tu_type_dict, tu_macro_dict, tu_var_dict, tu_item_dict = parse_file(root_dir, tu, file_cache, global_type_dict, global_macro_dict, global_var_dict)




    (relevant_header_set, content_range, function_code,
     fun_item_dict, macro_expr_info_list, callee_info_list,
     function_cursor, func_type, ret_range_list, unparsed_fun_set) \
        = parse_function(root_dir, file_path, function_name, tu, file_cache,
                         tu_dict, tu_item_dict, tu_type_dict,function_info_dict)

    
