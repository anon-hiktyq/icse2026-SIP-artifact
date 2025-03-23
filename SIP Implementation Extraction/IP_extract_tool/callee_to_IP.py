from build_info_dict import *
from extract_all import get_type_name
import tree_sitter_c as tspython
from tree_sitter import Language, Parser
import re
from utils import record_content_range, record_range_content
# 初始化 tree-sitter
C_LANGUAGE = Language(tspython.language())
parser = Parser(C_LANGUAGE)


def get_node_range(node, node_range = None):
    """获取node的范围"""

    if not node_range is None:
        condition_abs_range = (
            node_range[0] + node.start_point[0],  # start_line
            node.start_point[1] if node.start_point[0] == 0 else node_range[1] + node.start_point[1],  # start_col
            node_range[0] + node.end_point[0],    # end_line
            node.end_point[1] if node.end_point[0] == 0 else node_range[1] + node.end_point[1]   # end_col
        )
    else:
        condition_abs_range = (node.start_point[0], node.start_point[1], node.end_point[0], node.end_point[1])
    return condition_abs_range


def get_callee_context(function_code, callee_info_list, macro_expr_info_list):
    """
    使用 tree-sitter 获取函数中所有被调用函数和含参宏的上下文信息

    :param function_code: 函数的源代码
    :param callee_info_list: 被调用函数的信息列表
    :param macro_expr_info_list: 含参宏的信息列表，默认为None
    :return: 节点与被调用函数/宏的映射字典 node_item_map，格式为 {ts_node: {'type': 'callee'/'macro', 'info': callee_info/macro_info}}
    """
    node_item_map = {}

    # 解析代码
    tree = parser.parse(bytes(function_code, 'utf8'))
    root_node = tree.root_node

    # 创建一个映射，将callee的范围映射到callee_info
    callee_range_to_info = {}
    for callee in callee_info_list:
        # 将callee的范围转换为tree-sitter的格式
        start_point = (callee.content_range[0], callee.content_range[1])
        end_point = (callee.content_range[2], callee.content_range[3])
        callee_range_to_info[(start_point, end_point)] = callee

    # 创建一个映射，将macro的范围映射到macro_info
    macro_range_to_info = {}
    if macro_expr_info_list:
        for macro in macro_expr_info_list:
            # 将macro的范围转换为tree-sitter的格式
            start_point = (macro.content_range[0], macro.content_range[1])
            end_point = (macro.content_range[2], macro.content_range[3])
            macro_range_to_info[(start_point, end_point)] = macro

    # 查找所有函数调用节点和宏调用节点
    def find_call_expressions(node):
        """递归查找所有函数调用节点和宏调用节点"""
        if not node:
            return

        # 如果是函数调用表达式或可能是宏调用
        if node.type == 'call_expression' or node.type == 'macro_expression':
            # 检查是否匹配任何callee
            for (start, end), callee in callee_range_to_info.items():
                if (node.start_point[0] == start[0] and node.start_point[1] == start[1] and
                    node.end_point[0] == end[0] and node.end_point[1] == end[1]):

                    # 找到包含该调用的最近的语句或控制结构
                    context_node = find_statement_context(node)

                    # 将上下文节点和callee信息添加到映射中
                    node_item_map[context_node] = {'type': 'callee', 'info': callee}

            # 检查是否匹配任何macro
            for (start, end), macro in macro_range_to_info.items():
                if (node.start_point[0] == start[0] and node.start_point[1] == start[1] and
                    node.end_point[0] == end[0] and node.end_point[1] == end[1]):

                    # 找到包含该调用的最近的语句或控制结构
                    context_node = find_statement_context(node)

                    # 将上下文节点和macro信息添加到映射中
                    node_item_map[context_node] = {'type': 'macro', 'info': macro}

        # 递归处理子节点
        for child in node.named_children:
            find_call_expressions(child)

    def find_statement_context(node):
        """
        找到包含给定节点的最近的语句或控制结构
        """
        current = node
        parent = current.parent

        # 向上查找，直到找到语句或控制结构
        while parent:
            # 如果父节点是语句或控制结构，返回父节点
            if parent.type in [
                'expression_statement',  # 表达式语句
                'declaration',           # 声明语句
                'if_statement',          # if语句
                'switch_statement',      # switch语句
                'while_statement',       # while循环
                'for_statement',         # for循环
                'do_statement',          # do-while循环
                'return_statement',      # return语句
                'compound_statement'     # 复合语句（代码块）
            ]:
                return parent

            # 如果当前节点已经是函数定义的直接子节点，返回当前节点
            if parent.type == 'function_definition':
                return current

            # 继续向上查找
            current = parent
            parent = current.parent

        # 如果没有找到合适的上下文，返回节点本身
        return node

    # 开始查找所有函数调用节点和宏调用节点
    find_call_expressions(root_node)

    return node_item_map

def create_ip_expr(callee, fun_var_dict, ip_call_code_list, ret_def_dict, function_info_dict, rank_dict):
    """
    将函数调用转换为IPCALL的形式，生成所有的IPCALL和对应的ret及其声明

    :param callee: 函数信息
    :param fun_var_dict: 函数变量字典
    :param ip_call_code_list: IP调用代码列表
    :param ret_def_dict: 返回值定义字典
    :param function_info_dict: 函数信息字典
    :param rank_dict: 函数排名字典
    :return: 无返回值，直接修改传入的列表和字典
    """
    # 处理子函数
    if callee.sub_function_info_list:
        for sub_function_info in callee.sub_function_info_list:
            create_ip_expr(sub_function_info, fun_var_dict, ip_call_code_list, ret_def_dict, function_info_dict, rank_dict)

    var_mapping = callee.var_mapping
    var_list = []

    # 获取函数类型
    func_type = function_info_dict[callee.name].func_type

    # 计算rank - 在定义ret之前计算
    if callee.name not in rank_dict:
        rank_dict[callee.name] = 0
    rank = rank_dict[callee.name]
    rank_dict[callee.name] += 1

    # 为非void函数添加ret
    if func_type != 'void':
        # 使用rank来命名返回值，确保与函数调用的rank一致
        ret_name = f'{callee.name}_ret_{rank}'
        is_pointer = '*' in func_type
        ret_def = f'{func_type} {ret_name};'
        ret_def_dict[ret_name] = {'secondary_range': callee.content_range, 'ret_type': func_type}

        # 添加到var_mapping
        var_mapping['ret'] = {'arg': f'{"&" if not is_pointer else ""}{ret_name}', 'type': 'variable'}

        # 将ret_def添加到IPCALL代码列表
        ip_call_code_list.append(f'{ret_def}')

    # 处理var_mapping中的参数
    for key, arg_info in var_mapping.items():
        if arg_info['type'] == 'function':
            # 查找对应的子函数
            for sub_function in callee.sub_function_info_list:
                if sub_function.body in arg_info['arg']:
                    for ret_name, ret_info in ret_def_dict.items():
                        if tuple(ret_info['secondary_range']) == tuple(sub_function.content_range):
                            arg_info['arg'] = arg_info['arg'].replace(sub_function.body, ret_name)
                            break

        # 如果出现在fun_var_dict,代表该参数包含在IP Struct内
        if get_type_name(arg_info["arg"]) in fun_var_dict:
            var_list.append(f'.{key} = pIp->{arg_info["arg"]}')
        else:
            var_list.append(f'.{key} = {arg_info["arg"]}')

    # 生成IPCALL语句
    if var_list:
        ip_call = ','.join([f'IPCALL({callee.name}', f'ip{callee.name}_{rank}', ",".join(var_list)]) + ');'
    else:
        ip_call = ','.join([f'IPCALL({callee.name}', f'ip{callee.name}_{rank}']) + ');'
    ip_call_code_list.append(ip_call)


def replace_var_with_ip_struct(content, fun_var_dict):
    """
    将content中出现的fun_var_dict中的变量替换为pIp->name的形式，
    但不处理IPCALL内部的变量，因为它们已经在create_ip_expr中处理过了

    :param content: 需要处理的内容
    :param fun_var_dict: 函数变量字典
    :return: 处理后的内容
    """
    # 首先将IPCALL语句提取出来，避免处理它们内部的变量
    ipcall_pattern = r'IPCALL\([^)]+\);'
    ipcall_matches = re.finditer(ipcall_pattern, content)

    # 保存IPCALL语句及其位置
    ipcall_regions = []
    for match in ipcall_matches:
        start, end = match.span()
        ipcall_regions.append((start, end, match.group()))

    # 如果没有IPCALL语句，直接处理整个内容
    if not ipcall_regions:
        # 创建一个变量名列表，按长度降序排序以避免部分匹配问题
        var_names = sorted(fun_var_dict.keys(), key=len, reverse=True)

        # 对每个变量名进行替换
        modified_content = content
        for var_name in var_names:
            # 使用正则表达式确保只匹配完整的变量名
            pattern = r'\b' + f'{var_name}' + r'\b'
            modified_content = re.sub(pattern, f'pIp->{var_name}', modified_content)

        return modified_content

    # 处理IPCALL语句之外的部分
    result = []
    last_end = 0

    for start, end, ipcall_text in ipcall_regions:
        # 处理IPCALL前的部分
        if start > last_end:
            segment = content[last_end:start]
            # 替换这部分中的变量
            var_names = sorted(fun_var_dict.keys(), key=len, reverse=True)
            for var_name in var_names:
                pattern = r'\b' + f'{var_name}' + r'\b'
                segment = re.sub(pattern, f'pIp->{var_name}', segment)
            result.append(segment)

        # 保持IPCALL语句不变
        result.append(ipcall_text)
        last_end = end

    # 处理最后一个IPCALL之后的部分
    if last_end < len(content):
        segment = content[last_end:]
        var_names = sorted(fun_var_dict.keys(), key=len, reverse=True)
        for var_name in var_names:
            pattern = r'\b' + f'{var_name}' + r'\b'
            segment = re.sub(pattern, f'pIp->{var_name}', segment)
        result.append(segment)

    return ''.join(result)

def replace_at_position(original_text, replacements):
    """
    根据位置信息替换文本中的内容

    :param original_text: 原始文本
    :param replacements: 替换信息列表，每项为 (start_line, start_col, end_line, end_col, replacement_text)
    :return: 替换后的文本
    """
    # 将文本分割成行
    lines = original_text.split('\n')

    # 按照行和列的逆序排序替换项，以避免位置变化影响后续替换
    replacements = sorted(replacements, key=lambda x: (x[2], x[3], x[0], x[1]), reverse=True)

    # 执行替换
    for start_line, start_col, end_line, end_col, replacement_text in replacements:
        # 如果是单行替换
        if start_line == end_line:
            line = lines[start_line]
            lines[start_line] = line[:start_col] + replacement_text + line[end_col:]
        else:
            # 多行替换
            # 处理第一行
            lines[start_line] = lines[start_line][:start_col] + replacement_text.split('\n')[0]

            # 删除中间的行
            for i in range(start_line + 1, end_line):
                lines[i] = ""

            # 处理最后一行
            if len(replacement_text.split('\n')) > 1:
                last_part = replacement_text.split('\n')[-1]
            else:
                last_part = ""

            lines[end_line] = last_part + lines[end_line][end_col:]

    # 重新组合文本，移除空行
    return '\n'.join([line for line in lines if line != ""])

def exal_relative_content_range(secondary_range_tuple, first_range):
    """
    将secondary_range转换为对于first_range的相对位置
    """
    secondary_range = list(secondary_range_tuple)
    rel_start_line = secondary_range[0] - first_range[0]
    rel_start_col = secondary_range[1] - (first_range[1] if secondary_range[0] == first_range[0] else 0)
    rel_end_line = secondary_range[2] - first_range[0]
    rel_end_col = secondary_range[3] - (first_range[1] if secondary_range[2] == first_range[0] else 0)
    return (rel_start_line, rel_start_col, rel_end_line, rel_end_col)

def apply_replacements_to_context(context_content, item_replacements, node_range):
    """
    将 item_replacements 中的内容替换到上下文代码中

    :param context_content: 上下文代码内容
    :param item_replacements: 项目替换映射
    :param node_range: 节点范围
    :return: 修改后的上下文代码
    """
    # 准备替换列表
    replacements = []

    # 将每个需要替换的项目转换为相对于上下文的位置
    for content_range_tuple, replacement in item_replacements.items():
        # 将 content_range 转换为相对于 node_range 的位置
        rel_content_range = exal_relative_content_range(content_range_tuple, node_range)

        # 添加到替换列表
        replacements.append((rel_content_range[0], rel_content_range[1],
                            rel_content_range[2], rel_content_range[3],
                            replacement))

    # 应用替换
    if replacements:
        modified_content = replace_at_position(context_content, replacements)
        return modified_content

    return context_content

def process_expression_statement(node_range, function_code, ip_call_code_list, item_replacements, fun_var_dict):
    """
    处理表达式语句

    :param node_range: 节点范围
    :param function_code: 函数代码
    :param ip_call_code_list: IP调用代码列表
    :param item_replacements: 项目替换映射
    :param fun_var_dict: 函数变量字典
    :return: 修改后的内容和范围
    """
    # 步骤2: 提取需要修改的上下文代码
    original_content = record_range_content(function_code, node_range)

    # 步骤3: 将提取的上下文代码进行修改(替换item_replacements中的内容)
    modified_content = apply_replacements_to_context(original_content, item_replacements, node_range)

    # 如果所有函数调用都被删除，会剩余一个';'，删去
    modified_content = modified_content.strip()
    if modified_content and modified_content.strip() == ';':
        modified_content = ''

    # 步骤4: 在合适的地方插入ip_call_code_list
    # 步骤5: 在上下文最开头添加"{"，在上下文末尾添加'}'
    if ip_call_code_list or modified_content:
        # 如果有IP调用代码或修改后的内容不为空，添加花括号
        modified_content = '{' + ''.join(ip_call_code_list) + modified_content + '}'
    else:
        # 如果没有IP调用代码且修改后的内容为空，返回空字符串
        modified_content = ''

    # 步骤6: 修改相应变量为'pIp->{name}'的形式
    modified_content = replace_var_with_ip_struct(modified_content, fun_var_dict)

    return (node_range, modified_content)


def process_declaration(root_node, node_range, function_code, ip_call_code_list, item_replacements, fun_var_dict):
    """
    处理声明语句，例如 int a = funa() + b;
    将其拆分为声明部分和赋值部分，例如 int a; {ip_call_code_list a = funa_ret_0 + b;}

    :param node_range: 节点范围
    :param function_code: 函数代码
    :param ip_call_code_list: IP调用代码列表
    :param item_replacements: 项目替换映射
    :return: 修改后的内容和范围
    """

    # print(f'该上下文源代码:{root_node.text.decode('UTF-8')}')
    # 步骤2: 提取需要修改的上下文代码
    original_content = record_range_content(function_code, node_range)

    # # 解析声明语句
    # tree = parser.parse(bytes(original_content, 'utf8'))
    # root_node = tree.root_node

    # 查找声明的变量类型、名称和初始化表达式
    var_type = ""
    var_name = None
    init_expr = None
    init_node = None


    type_parts = []
    declarator_node = None


    for child in root_node.children:
        # 收集所有类型相关节点（包括修饰符、类型名等）
        if child.type in ['primitive_type', 'type_identifier', 'struct_specifier',
                              'union_specifier', 'enum_specifier', 'storage_class_specifier',
                              'type_qualifier', 'sized_type_specifier']:
            type_parts.append(record_range_content(function_code, get_node_range(child)))
        elif child.type == 'init_declarator':
            # print('找到了init_declarator')

            declarator_node = child
            # print(f'该上下文源代码:{declarator_node.text.decode('UTF-8')}')
            # 组合类型部分
            for init_child in declarator_node.children:
                if init_child.type == 'identifier':
                    var_name = record_range_content(function_code, get_node_range(init_child))
                    # print(f'var_name:{var_name}')
                elif init_child.type in ['pointer_declarator', 'array_declarator']:
                    # 处理指针或数组声明符
                    for ptr_child in init_child.children:
                        if ptr_child.type == 'identifier':
                            var_name = record_range_content(function_code, get_node_range(ptr_child))
                            # 添加指针或数组修饰符到类型
                            # var_type += ' ' + record_range_content(function_code, (init_child.start_point[0], init_child.start_point[1], ptr_child.start_point[0], init_child.start_point[1]))
                elif init_child.type == '=':
                    # 找到等号后面的初始化表达式
                    for eq_sibling in declarator_node.children:
                        if eq_sibling.start_byte > init_child.start_byte:
                            init_node = eq_sibling
                            init_expr = record_range_content(function_code, get_node_range(init_node))
                            break

    var_type = ' '.join(type_parts)
    # print('var_type:', var_type)
    # 如果无法解析，返回原始内容
    if not var_name:
        return (node_range, original_content)

    modified_init_expr_range = get_node_range(init_node)
    # # 步骤3: 将提取的上下文代码进行修改(替换item_replacements中的内容)
    modified_init_expr = apply_replacements_to_context(init_expr, item_replacements, modified_init_expr_range) if init_expr else None

    # print(f'init_expr:{init_expr}')
    # print(f'modified_init_expr:{modified_init_expr}')



    # 构建新的声明和赋值语句
    # 确保类型说明符包含所有必要的修饰符（如指针星号）
    if var_type and not var_type.endswith(' '):
        var_type += ' '

    # 构建新的声明语句（不包含初始化）
    declaration = f"{var_type}{var_name};"

    # 构建新的赋值语句
    assignment = ""
    if modified_init_expr:
        assignment = f"{var_name} = {modified_init_expr};"

    # 步骤4: 在合适的地方插入ip_call_code_list
    # 步骤5: 在上下文最开头添加"{"，在上下文末尾添加'}'
    if assignment:
        # 如果有赋值语句，将IP调用代码和赋值语句组合在一起
        modified_content = f"{declaration}{{{' '.join(ip_call_code_list)}{assignment}}}"
    else:
        # 如果没有赋值语句，只保留声明语句
        modified_content = declaration

    # 步骤6: 修改相应变量为'pIp->{name}'的形式
    modified_content = replace_var_with_ip_struct(modified_content, fun_var_dict)

    return (node_range, modified_content)


def process_control_statement(root_node, node_range, function_code, ip_call_code_list, item_replacements, fun_var_dict):
    """
    处理控制语句，如if和switch语句，只关注条件判断表达式部分

    :param root_node: 控制语句节点
    :param node_range: 节点范围
    :param function_code: 函数代码
    :param ip_call_code_list: IP调用代码列表
    :param item_replacements: 项目替换映射
    :param fun_var_dict: 函数变量字典
    :return: 两个元组：(开始范围, 修改后的开始内容), (结束范围, 结束内容)
    """
    # 步骤2: 提取需要修改的上下文代码
    original_content = record_range_content(function_code, node_range)
    print(f'original_content{original_content}')
    # 查找条件表达式节点（括号内的表达式）
    condition_node = None
    for child_node in root_node.children:
        if child_node.type == 'parenthesized_expression':
            print('Found parenthesized_expression')
            condition_node = child_node
            break
    
    # 如果找不到条件表达式，返回原始内容和空的结束元组
    if not condition_node:
        return [(node_range, original_content), None]

    # 获取条件表达式的范围和内容
    condition_range = get_node_range(condition_node)

    condition_content = record_range_content(function_code, condition_range)
    print(f'condition_content{condition_content}')
    # condition_content = condition_content.strip('()')  # 去掉括号

    # 步骤3: 将提取的上下文代码进行修改(替换item_replacements中的内容)
    modified_condition = apply_replacements_to_context(condition_content, item_replacements, condition_range)
    print(f'modified_condition{modified_condition}')

    # 构建修改后的控制语句开头部分
    # 将原始内容分为三部分：条件前、条件、条件后
    before_condition = record_range_content(function_code, (node_range[0], node_range[1], condition_range[0], condition_range[1]))

    # 组合修改后的内容
    modified_content = before_condition + modified_condition
    print(f'modified_content{modified_content}')

    # 步骤4: 在合适的地方插入ip_call_code_list
    # 步骤5: 在上下文最开头添加"{"
    if ip_call_code_list:
        # 在控制语句的开头添加 { 和 IP调用代码
        modified_content = '{' + ''.join(ip_call_code_list) + modified_content
    else:
        # 如果没有IP调用代码，仍然需要添加开始括号
        modified_content = '{' + modified_content
    
    # 步骤6: 修改相应变量为'pIp->{name}'的形式
    modified_content = replace_var_with_ip_struct(modified_content, fun_var_dict)
    print(f'modified_content{modified_content}')
    
    # 创建结束括号的元组（在上下文末尾添加'}'）
    # 计算控制语句的结束位置
    end_line = node_range[2]
    end_col = node_range[3]
    end_range = (end_line, end_col, end_line, end_col)

    # 返回两个元组：开始部分和结束括号
    return [((node_range[0], node_range[1], condition_range[2], condition_range[3]), modified_content), (end_range, '}')]


def process_return_statement(root_node, node_range, function_code, ip_call_code_list, item_replacements, fun_var_dict, function_info):
    """
    处理返回语句，不修改 return 关键字，只处理表达式部分

    :param node_range: 节点范围
    :param function_code: 函数代码
    :param ip_call_code_list: IP调用代码列表
    :param item_replacements: 项目替换映射
    :param fun_var_dict: 函数变量字典
    :param function_info: 函数信息
    :return: 修改后的内容和范围
    """
    # 步骤2: 提取需要修改的上下文代码
    original_content = record_range_content(function_code, node_range)
    
    # 查找返回表达式
    return_node = None
    return_expr_range = None
    return_expr = None
    
    for return_child in root_node.children:
        if return_child.type != 'return':
            return_node = return_child
            return_expr_range = get_node_range(return_node)
            return_expr = record_range_content(function_code, return_expr_range)
            break
    
    # # 如果是空的return语句，直接返回空字符串
    # if not return_expr:
    #     return (node_range, '')
    
    # 获取返回表达式的范围

    print(f'return_expr: {return_expr}')
    # 步骤3: 将提取的上下文代码进行修改(替换item_replacements中的内容)
    modified_expr = apply_replacements_to_context(return_expr, item_replacements, return_expr_range)
    print(f'modified_expr{modified_expr}')
    # 步骤4: 在合适的地方插入ip_call_code_list
    # 步骤5: 在上下文最开头添加"{"，在上下文末尾添加'}'
    if ip_call_code_list:
        # 在return语句前插入IP调用代码
        modified_content = ''.join(ip_call_code_list)
        
        # 创建IP调用代码的插入位置（在return语句前）
        ip_call_range = (node_range[0], node_range[1], node_range[0], node_range[1])
        
        # 步骤6: 修改相应变量为'pIp->{name}'的形式
        modified_content = replace_var_with_ip_struct(modified_content, fun_var_dict)
        
        # 返回两个修改：IP调用代码和表达式修改
        return [(ip_call_range, modified_content), (return_expr_range, modified_expr)]
    else:
        # 如果没有IP调用代码，只返回表达式修改
        return [(return_expr_range, modified_expr)]


def apply_replacements_to_clause(clause_content, replacements):
    """
    应用替换到子句内容

    :param clause_content: 子句内容
    :param replacements: 替换列表
    :return: 修改后的子句内容
    """
    if replacements and clause_content:
        return replace_at_position(clause_content, replacements)
    return clause_content


def find_replacements_in_range(content_range_tuple, node_range, clause_node, item_replacements):
    """
    查找在指定范围内的替换项

    :param content_range_tuple: 内容范围元组
    :param node_range: 节点范围
    :param clause_node: 子句节点
    :param item_replacements: 项目替换映射
    :return: 替换列表
    """
    replacements = []

    # 计算绝对位置
    abs_start_line = node_range[0] + clause_node.start_point[0]
    abs_start_col = clause_node.start_point[1] if clause_node.start_point[0] == 0 else node_range[1] + clause_node.start_point[1]

    # 检查函数调用是否在子句范围内
    if (abs_start_line <= content_range_tuple[0] <= abs_start_line + clause_node.end_point[0] - clause_node.start_point[0] and
            abs_start_line <= content_range_tuple[2] <= abs_start_line + clause_node.end_point[0] - clause_node.start_point[0]):

        # 计算相对位置
        rel_start_line = content_range_tuple[0] - abs_start_line
        rel_start_col = content_range_tuple[1] - abs_start_col if rel_start_line == 0 else content_range_tuple[1]
        rel_end_line = content_range_tuple[2] - abs_start_line
        rel_end_col = content_range_tuple[3] - abs_start_col if rel_end_line == 0 else content_range_tuple[3]

        # 添加到替换列表
        replacements.append((rel_start_line, rel_start_col, rel_end_line, rel_end_col, item_replacements[content_range_tuple]))

    return replacements



def add_braces_and_condition(body_node, node_range, has_braces, ip_call_prefix, condition_check, update_code=""):
    """
    添加花括号和条件检查代码

    :param body_node: 函数体节点
    :param node_range: 节点范围
    :param has_braces: 是否已有花括号
    :param ip_call_prefix: IP调用前缀
    :param condition_check: 条件检查代码
    :param update_code: 更新代码（用于for循环）
    :return: 修改列表
    """
    modifications = []

    if not has_braces:
        # 函数体开始位置添加左花括号
        body_start = (node_range[0] + body_node.start_point[0], body_node.start_point[1],
                      node_range[0] + body_node.start_point[0], body_node.start_point[1])
        modifications.append((body_start, "{"))

        # 函数体结束位置添加条件判断和右花括号
        body_end = (node_range[0] + body_node.end_point[0], body_node.end_point[1],
                    node_range[0] + body_node.end_point[0], body_node.end_point[1])
        modifications.append((body_end, f"{ip_call_prefix}{condition_check} {update_code}}}"))
    else:
        # 函数体已有花括号，在右花括号前添加条件判断
        # 找到右花括号的位置
        for i in range(len(body_node.children)):
            if body_node.children[i].type == '}':
                brace_node = body_node.children[i]
                brace_pos = (node_range[0] + brace_node.start_point[0], brace_node.start_point[1],
                            node_range[0] + brace_node.start_point[0], brace_node.start_point[1])
                modifications.append((brace_pos, f"{ip_call_prefix}{condition_check} {update_code}}}"))
                break
        else:
            # 如果没有找到右花括号，在函数体结束位置添加条件判断
            body_end = (node_range[0] + body_node.end_point[0], body_node.end_point[1],
                        node_range[0] + body_node.end_point[0], body_node.end_point[1])
            modifications.append((body_end, f"{ip_call_prefix}{condition_check} {update_code}"))

    return modifications

def process_for_statement(node_range, function_code, ip_call_code_list, item_replacements, fun_var_dict):
    """
    处理 for 循环语句，将其转换为 while(true) 循环

    :param node_range: 节点范围
    :param function_code: 函数代码
    :param ip_call_code_list: IP调用代码列表
    :param item_replacements: 项目替换映射
    :param fun_var_dict: 函数变量字典
    :return: 包含多个修改元组的列表
    """
    # 获取原始内容
    original_content = record_range_content(function_code, node_range)

    # 解析 for 循环语句
    tree = parser.parse(bytes(original_content, 'utf8'))
    root_node = tree.root_node

    # 查找 for 语句的三个子句和函数体
    init_clause = None
    condition_clause = None
    update_clause = None
    body_node = None

    for child in root_node.children:
        if child.type == 'for_statement':
            # 查找 for 语句的子节点
            for for_child in child.children:
                if for_child.type == 'for_clause':
                    # 查找 for 子句中的三个部分
                    clause_parts = for_child.children
                    for i, part in enumerate(clause_parts):
                        if part.type == ';':
                            continue

                        # 根据位置确定是哪个子句
                        if i < 2:  # 初始化子句
                            init_clause = part
                        elif i < 4:  # 条件判断子句
                            condition_clause = part
                        else:  # 递归子句
                            update_clause = part

                elif for_child.type in ['compound_statement', 'expression_statement', 'declaration']:
                    body_node = for_child

    # 如果找不到函数体，返回原始内容
    if not body_node:
        return [(node_range, original_content)]

    # 获取各个子句的内容
    init_content = ""
    condition_content = "true"  # 默认为 true
    update_content = ""

    if init_clause:
        init_content = original_content[init_clause.start_byte:init_clause.end_byte]

    if condition_clause:
        condition_content = original_content[condition_clause.start_byte:condition_clause.end_byte]

    if update_clause:
        update_content = original_content[update_clause.start_byte:update_clause.end_byte]

    # 应用替换到各个子句
    modified_init = apply_replacements_to_clause(init_content, item_replacements)
    modified_condition = apply_replacements_to_clause(condition_content, item_replacements)
    modified_update = apply_replacements_to_clause(update_content, item_replacements)

    # 创建修改列表
    modifications = []

    # 1. 添加初始化子句（如果有）
    if modified_init:
        # 在 for 循环前添加初始化语句
        init_statement = f"{modified_init};"
        init_statement = replace_var_with_ip_struct(init_statement, fun_var_dict)

        # 添加到修改列表
        init_range = (node_range[0], node_range[1], node_range[0], node_range[1])
        modifications.append((init_range, init_statement))

    # 2. 修改 for 循环头部为 while(true)
    for_header_end = None
    for child in root_node.children:
        if child.type == 'for_statement':
            for for_child in child.children:
                if for_child.type == 'for_clause':
                    for_header_end = (node_range[0] + for_child.end_point[0], for_child.end_point[1])
                    break
            break

    if for_header_end:
        # 替换 for(...) 为 while(true)
        for_header_range = (node_range[0], node_range[1], for_header_end[0], for_header_end[1])
        modifications.append((for_header_range, "while(true)"))

    # 3. 检查函数体是否有花括号
    has_braces = body_node.type == 'compound_statement'

    # 4. 创建条件判断和递归子句代码
    # 添加IP调用代码
    ip_call_prefix = ''.join(ip_call_code_list) if ip_call_code_list else ''

    # 创建条件判断语句
    condition_check = f"if (!({modified_condition})) break;"

    # 替换变量为IP结构体形式
    condition_check = replace_var_with_ip_struct(condition_check, fun_var_dict)
    modified_update = replace_var_with_ip_struct(modified_update, fun_var_dict)

    # 添加花括号和条件检查
    modifications.extend(add_braces_and_condition(body_node, node_range, has_braces, ip_call_prefix, condition_check, modified_update))

    # 5. 在整个 for 循环的开始和结束位置添加花括号
    # 开始位置
    start_range = (node_range[0], node_range[1], node_range[0], node_range[1])
    modifications.append((start_range, "{"))

    # 结束位置
    end_range = (node_range[2], node_range[3], node_range[2], node_range[3])
    modifications.append((end_range, "}"))

    return modifications

def process_loop_statement(node_range, function_code, ip_call_code_list, item_replacements, fun_var_dict):
    """
    处理循环语句（while和do-while），将条件判断移到循环体内部

    :param node_range: 节点范围
    :param function_code: 函数代码
    :param ip_call_code_list: IP调用代码列表
    :param item_replacements: 项目替换映射
    :param fun_var_dict: 函数变量字典
    :return: 包含多个修改元组的列表
    """
    # 步骤2: 提取需要修改的上下文代码
    original_content = record_range_content(function_code, node_range)

    # 解析循环语句
    tree = parser.parse(bytes(original_content, 'utf8'))
    root_node = tree.root_node

    # 查找循环类型和条件表达式
    is_do_while = False
    condition_node = None
    body_node = None

    for child in root_node.children:
        if child.type == 'while_statement':
            # 查找while语句的条件和函数体
            for while_child in child.children:
                if while_child.type == 'parenthesized_expression':
                    condition_node = while_child
                elif while_child.type in ['compound_statement', 'expression_statement', 'declaration']:
                    body_node = while_child
        elif child.type == 'do_statement':
            is_do_while = True
            # 查找do-while语句的条件和函数体
            for do_child in child.children:
                if do_child.type == 'parenthesized_expression':
                    condition_node = do_child
                elif do_child.type in ['compound_statement', 'expression_statement', 'declaration']:
                    body_node = do_child

    # 如果找不到条件表达式或函数体，返回原始内容
    if not condition_node or not body_node:
        return [(node_range, original_content)]

    # 获取条件表达式的内容
    condition_content = original_content[condition_node.start_byte:condition_node.end_byte]
    condition_content = condition_content.strip('()')  # 去掉括号

    # 步骤3: 将提取的上下文代码进行修改(替换item_replacements中的内容)
    modified_condition = apply_replacements_to_context(condition_content, item_replacements, node_range)

    # 创建修改列表
    modifications = []

    # 1. 修改循环头部
    if is_do_while:
        # do-while循环，保持do关键字不变
        loop_header = original_content[:condition_node.start_byte]
        modifications.append((node_range[:2] + [node_range[0] + condition_node.start_point[0], condition_node.start_point[1]], loop_header))
    else:
        # while循环，将条件替换为true
        loop_header = original_content[:condition_node.end_byte].replace(condition_content, "true")
        modifications.append((node_range[:2] + [node_range[0] + condition_node.end_point[0], condition_node.end_point[1]], loop_header))

    # 2. 检查函数体是否有花括号
    has_braces = body_node.type == 'compound_statement'

    # 步骤4: 在合适的地方插入ip_call_code_list
    # 步骤5: 在上下文最开头添加"{"，在上下文末尾添加'}'
    # 创建条件判断语句
    condition_check = f"if (!({modified_condition})) break;"

    # 步骤6: 修改相应变量为'pIp->{name}'的形式
    condition_check = replace_var_with_ip_struct(condition_check, fun_var_dict)

    # 添加IP调用代码
    ip_call_prefix = ''.join(ip_call_code_list) if ip_call_code_list else ''

    # 添加花括号和条件检查
    if not has_braces:
        # 函数体开始位置添加左花括号
        body_start = (node_range[0] + body_node.start_point[0], body_node.start_point[1],
                      node_range[0] + body_node.start_point[0], body_node.start_point[1])
        modifications.append((body_start, "{"))

        # 函数体结束位置添加条件判断和右花括号
        body_end = (node_range[0] + body_node.end_point[0], body_node.end_point[1],
                    node_range[0] + body_node.end_point[0], body_node.end_point[1])
        modifications.append((body_end, f"{ip_call_prefix}{condition_check}}}"))
    else:
        # 函数体已有花括号，在右花括号前添加条件判断
        # 找到右花括号的位置
        for i in range(len(body_node.children)):
            if body_node.children[i].type == '}':
                brace_node = body_node.children[i]
                brace_pos = (node_range[0] + brace_node.start_point[0], brace_node.start_point[1],
                            node_range[0] + brace_node.start_point[0], brace_node.start_point[1])
                modifications.append((brace_pos, f"{ip_call_prefix}{condition_check}}}"))
                break
        else:
            # 如果没有找到右花括号，在函数体结束位置添加条件判断
            body_end = (node_range[0] + body_node.end_point[0], body_node.end_point[1],
                        node_range[0] + body_node.end_point[0], body_node.end_point[1])
            modifications.append((body_end, f"{ip_call_prefix}{condition_check}"))

    # 4. 如果是do-while循环，需要删除原始的while条件部分
    if is_do_while:
        # 找到while关键字和条件表达式的范围
        while_start = None
        for i in range(len(root_node.children)):
            if root_node.children[i].type == 'while':
                while_node = root_node.children[i]
                while_start = (node_range[0] + while_node.start_point[0], while_node.start_point[1],
                              node_range[0] + condition_node.end_point[0], condition_node.end_point[1])
                break

        if while_start:
            modifications.append((while_start, ""))  # 删除while和条件部分

    # 5. 在整个循环的开始位置添加花括号
    start_range = (node_range[0], node_range[1], node_range[0], node_range[1])
    modifications.append((start_range, "{"))

    # 在整个循环的结束位置添加花括号
    end_range = (node_range[2], node_range[3], node_range[2], node_range[3])
    modifications.append((end_range, "}"))

    return modifications


def process_context_node(ts_node, node_item_map, function_code, function_info_dict, fun_var_dict, rank_dict,
                         function_name):
    """
    处理上下文节点，为其中的函数调用和宏生成IP表达式

    :param ts_node: 上下文节点
    :param node_item_map: 节点与被调用函数/宏的映射字典
    :param function_code: 函数代码
    :param function_info_dict: 函数信息字典
    :param fun_var_dict: 函数变量字典
    :param rank_dict: 函数排名字典，作为"全局变量"在整个转化过程中使用
    :return: 修改后的内容和范围
    """
    node_type = ts_node.type
    node_range = [ts_node.start_point[0], ts_node.start_point[1],
                  ts_node.end_point[0], ts_node.end_point[1]]

    # 找到该上下文中所有的callee和macro
    context_items = find_items_in_context(ts_node, node_item_map)

    # 为这些callee和macro生成ip_expr
    ip_call_code_list, ret_def_dict, item_replacements = generate_ip_exprs(context_items, function_info_dict, fun_var_dict, rank_dict)

    # 根据不同的上下文类型处理
    if node_type == 'expression_statement':
        return process_expression_statement(node_range, function_code, ip_call_code_list, item_replacements,
                                            fun_var_dict)
    elif node_type in ['if_statement', 'switch_statement']:
        return process_control_statement(ts_node, node_range, function_code, ip_call_code_list, item_replacements, fun_var_dict)
    elif node_type == 'declaration':
        return process_declaration(ts_node, node_range, function_code, ip_call_code_list, item_replacements, fun_var_dict)
    elif node_type == 'return_statement':
        return process_return_statement(ts_node, node_range, function_code, ip_call_code_list, item_replacements, fun_var_dict, function_info_dict[function_name])
    # elif node_type in ['while_statement', 'do_statement']:
    #     return process_loop_statement(node_range, function_code, ip_call_code_list, item_replacements, fun_var_dict)
    # elif node_type == 'for_statement':
    #     return process_for_statement(node_range, function_code, ip_call_code_list, item_replacements, fun_var_dict)
    # else:
    #     # 默认处理方式
    #     return process_default(ts_node, node_range, function_code, ip_call_code_list, ret_def_dict, item_replacements, fun_var_dict)

def find_items_in_context(context_node, node_item_map):
    """
    找到该上下文节点中所有的callee和macro(不包含其他上下文节点的callee和macro)

    :param context_node: 上下文节点
    :param node_item_map: 节点与被调用函数/宏的映射字典
    :return: 上下文中的项目列表，每项包含类型和信息
    """
    context_items = []

    # 遍历所有节点，找到属于该上下文的项目
    for node, item_info in node_item_map.items():
        if node == context_node:
            context_items.append(item_info)

    return context_items

def generate_ip_exprs(context_items, function_info_dict, fun_var_dict, rank_dict):
    """
    为上下文中的项目生成IP表达式

    :param context_items: 上下文中的项目列表
    :param function_info_dict: 函数信息字典
    :param fun_var_dict: 函数变量字典
    :param rank_dict: 函数排名字典，作为"全局变量"在整个转化过程中使用
    :return: IP调用代码列表、返回值定义字典和项目替换映射
    """
    ip_call_code_list = []
    ret_def_dict = {}
    item_replacements = {}  # 记录每个项目应该被替换成的代码

    # 首先处理所有的函数调用
    for item_info in context_items:
        item = item_info['info']

        if not item_info['type'] == 'macro':
            # 处理函数调用
            create_ip_expr(item, fun_var_dict, ip_call_code_list, ret_def_dict, function_info_dict, rank_dict)

            # 记录替换信息
            func_type = function_info_dict[item.name].func_type
            if func_type == 'void':
                # void函数调用应该被删除
                item_replacements[tuple(item.content_range)] = ''
            else:
                # 非void函数调用应该被替换为返回值
                for ret_name, ret_info in ret_def_dict.items():
                    if tuple(ret_info['secondary_range']) == tuple(item.content_range):
                        item_replacements[tuple(item.content_range)] = ret_name
                        break

    # 然后处理所有的宏调用
    for item_info in context_items:
        item = item_info['info']

        if item_info['type'] == 'macro':
            # 处理宏调用中的函数参数
            if item.sub_function_info_list:
                for sub_function in item.sub_function_info_list:
                    # 如果子函数还没有处理，先处理子函数
                    create_ip_expr(sub_function, fun_var_dict, ip_call_code_list, ret_def_dict, function_info_dict, rank_dict)

                    # # 更新宏的var_mapping
                    # for key, arg_info in item.var_mapping.items():
                    #     if arg_info['type'] == 'function' and sub_function.body in arg_info['arg']:
                    #         for ret_name, ret_info in ret_def_dict.items():
                    #             if tuple(ret_info['secondary_range']) == tuple(sub_function.content_range):
                    #                 arg_info['arg'] = arg_info['arg'].replace(sub_function.body, ret_name)
                    #                 item_replacements[tuple(sub_function.content_range)] = ret_name
                    #                 break

    return ip_call_code_list, ret_def_dict, item_replacements




def record_modified_range_and_content(function_name, function_info_dict, node_item_map, fun_var_dict):
    """
    记录修改后的范围和内容

    :param function_name: 函数名
    :param function_info_dict: 函数信息字典
    :param node_item_map: 节点与被调用函数/宏的映射字典
    :param fun_var_dict: 函数变量字典
    :return: 修改列表
    """
    code = function_info_dict[function_name].code
    modifications = []

    # 创建一个全局的rank_dict，用于在整个转化过程中跟踪函数调用的排名
    rank_dict = {}

    # 找到所有需要处理的上下文节点
    context_nodes = set()
    for node in node_item_map:
        # 找到包含该节点的上下文
        context_node = node
        while context_node and context_node.type not in [
            'expression_statement', 'declaration', 'if_statement',
            'switch_statement', 'default_statement',
            'while_statement', 'for_statement', 'do_statement',
            'return_statement', 'compound_statement'
        ]:
            context_node = context_node.parent

        if context_node:
            context_nodes.add(context_node)

    # 处理每个上下文节点
    for context_node in context_nodes:
        modification = process_context_node(context_node, node_item_map, code, function_info_dict, fun_var_dict,
                                            rank_dict, function_name)
        if modification:
            if isinstance(modification, tuple):
                modifications.append(modification)
            else:
                modifications.extend(modification)

    return modifications

def print_node_item_map(node_item_map, function_code):
    """
    打印节点与被调用函数/宏的映射关系

    :param node_item_map: 节点与被调用函数/宏的映射字典，格式为 {ts_node: {'type': 'callee'/'macro', 'info': callee_info/macro_info}}
    :param function_code: 函数的源代码
    """
    print("\n=== 节点与被调用函数/宏映射关系 ===\n")

    # 按节点类型对映射进行分组
    type_groups = {}
    for ts_node, item in node_item_map.items():
        node_type = ts_node.type
        if node_type not in type_groups:
            type_groups[node_type] = []

        # 获取节点范围
        block_range = [ts_node.start_point[0], ts_node.start_point[1],
                       ts_node.end_point[0], ts_node.end_point[1]]

        type_groups[node_type].append((block_range, item['info'], ts_node))

    # 为每种类型打印信息
    for node_type in sorted(type_groups.keys()):
        print(f"\n{node_type}:")
        print("=" * (len(node_type) + 1))

        for block_range, item, ts_node in type_groups[node_type]:
            # 提取该范围内的代码
            code_snippet = record_range_content(function_code, block_range)

            # 打印基本信息
            print(f"\n位置: 第 {block_range[0]+1} 行, 第 {block_range[1]+1} 列 到 第 {block_range[2]+1} 行, 第 {block_range[3]+1} 列")
            print(f"被调用函数/宏: {item.name}")
            print(f"函数定义文件: {item.file_path}")

            # 打印代码片段
            print("\n代码片段:")
            print("-" * 40)
            print(code_snippet)
            print("-" * 40)

            # 打印参数映射
            if item.var_mapping:
                print("\n参数映射:")
                for param, arg_info in item.var_mapping.items():
                    print(f"  {param} => {arg_info['arg']} ({arg_info['type']})")

            # 打印子函数信息
            if item.sub_function_info_list:
                print("\n子函数:")
                for sub_func in item.sub_function_info_list:
                    print(f"  - {sub_func.name}")

            print("\n" + "-" * 80 + "\n")


def print_modifications(modifications, function_code):
    """
    打印修改内容

    :param modifications: 修改列表
    :param function_code: 原始函数代码
    """
    print("\n=== 修改内容 ===\n")

    # 按照修改位置排序
    sorted_mods = sorted(modifications, key=lambda x: (x[0][0], x[0][1]))

    for mod in sorted_mods:
        if isinstance(mod, tuple):
            # 单个修改
            range_info, content = mod
            start_line, start_col, end_line, end_col = range_info

            # 获取原始内容
            original = record_range_content(function_code, range_info)

            print(f"位置: 第 {start_line+1} 行, 第 {start_col+1} 列 到 第 {end_line+1} 行, 第 {end_col+1} 列")
            print(f"原始内容: {original}")
            print(f"修改为: {content}")
            print("-" * 80)
        else:
            # 多个修改
            for sub_mod in mod:
                if sub_mod:
                    range_info, content = sub_mod
                    start_line, start_col, end_line, end_col = range_info

                    # 获取原始内容
                    original = record_range_content(function_code, range_info)

                    print(f"位置: 第 {start_line+1} 行, 第 {start_col+1} 列 到 第 {end_line+1} 行, 第 {end_col+1} 列")
                    print(f"原始内容: {original}")
                    print(f"修改为: {content}")
                    print("-" * 80)

def record_ret_range_and_content(function_info):
    """
    记录函数中所有 return 语句的范围和修改内容
    :param function_info: 函数信息对象
    :return: 修改列表 [(range, content), ...]
    """
    function_code = function_info.code
    tree = parser.parse(bytes(function_code, 'utf8'))
    root_node = tree.root_node

    func_type = function_info.func_type
    modifications = []
    
    # 如果函数类型是 void，不做任何修改
    if func_type == 'void':
        return modifications
    
    # 查找所有 return 语句
    def find_return_statements(node):
        if node.type == 'return_statement':
            # 找到 return 关键字节点
            for child in node.children:
                if child.type == 'return':
                    # 获取 return 关键字的范围
                    return_range = get_node_range(child)
                    
                    # 确定替换内容
                    is_pointer = '*' in func_type
                    if is_pointer:
                        replacement = 'pIp->ret = '
                    else:
                        replacement = '*(pIp->ret) = '
                    
                    modifications.append((return_range, replacement))
                    break
        
        # 递归处理子节点
        for child in node.children:
            find_return_statements(child)
    
    # 开始查找所有 return 语句
    find_return_statements(root_node)
    
    return modifications

def record_IP_var_pos(function_info, existing_modifications=None):
    """
    使用 tree-sitter 提取所有在 fun_var_dict 中的变量的范围，
    将这些变量转化为 pIp->{name} 的形式，记录在 modifications 中
    
    :param function_info: 函数信息对象
    :param existing_modifications: 已存在的修改列表，用于避免重复修改
    :return: 修改列表 [(range, content), ...]
    """
    function_code = function_info.code
    fun_var_dict = function_info.fun_var_dict
    
    # 如果没有需要处理的变量，直接返回空列表
    if not fun_var_dict:
        return []
    
    # 解析代码
    tree = parser.parse(bytes(function_code, 'utf8'))
    root_node = tree.root_node
    
    # 创建已存在修改范围的列表，用于检查是否有重叠
    existing_ranges = []
    if existing_modifications:
        for mod in existing_modifications:
            if isinstance(mod, tuple):
                range_info = mod[0]
                existing_ranges.append((range_info[0], range_info[1], range_info[2], range_info[3]))
            elif isinstance(mod, list):
                for sub_mod in mod:
                    if sub_mod:
                        range_info = sub_mod[0]
                        existing_ranges.append((range_info[0], range_info[1], range_info[2], range_info[3]))
    
    # 存储所有变量的修改
    modifications = []
    
    # 检查范围是否与已存在的修改重叠
    def is_overlapping(range1, range2):
        """检查两个范围是否重叠"""
        # 将范围转换为 (start_line, start_col, end_line, end_col) 格式
        start1 = (range1[0], range1[1])
        end1 = (range1[2], range1[3])
        start2 = (range2[0], range2[1])
        end2 = (range2[2], range2[3])
        
        # 检查是否重叠
        # 如果一个范围的开始在另一个范围的结束之后，或者一个范围的结束在另一个范围的开始之前，则不重叠
        if start1 > end2 or start2 > end1:
            return False
        return True
    
    # 查找所有标识符
    def find_identifiers(node, parent_node=None):
        # 如果是标识符节点
        if node.type == 'identifier':
            # 获取标识符文本
            node_range = get_node_range(node)
            identifier = record_range_content(function_code, node_range)
            
            # 检查是否在 fun_var_dict 中
            if identifier in fun_var_dict:
                # 检查是否与已存在的修改重叠
                overlapping = False
                for existing_range in existing_ranges:
                    if is_overlapping(node_range, existing_range):
                        overlapping = True
                        break
                
                if not overlapping:
                    # 检查父节点，避免修改结构体成员访问中的成员名
                    if parent_node and parent_node.type == 'field_expression':
                        # 如果是结构体成员访问中的成员名，跳过
                        for i, child in enumerate(parent_node.children):
                            if child == node and i > 0 and parent_node.children[i-1].type == '.':
                                return
                    
                    # 创建替换内容
                    replacement = f"(pIp->{identifier})"
                    
                    # 添加到修改列表
                    modifications.append((node_range, replacement))
        
        # 递归处理子节点
        for child in node.children:
            find_identifiers(child, node)
    
    # 开始查找所有标识符
    find_identifiers(root_node)
    
    return modifications

if __name__ == "__main__":
    # file_path = '../Input/SAMCode_V1.01/g4eapp.c'
    # # file_path = '../Input/test7/main.c'
    # root_dir = '../Input/SAMCode_V1.01'
    # bc_file_name = 'myproject'
    # function_name = 'TcProcess'

    file_path = '../Input/test19/test.c'
    root_dir = '../Input/test19'
    function_name = 'main'
    bc_file_name = 'myproject'

    # file_path = '../Input/lua/ldo.c'
    # root_dir = '../Input/lua'
    # function_name = 'luaD_seterrorobj'
    # bc_file_name = 'lua'


    global_type_dict = {}
    global_macro_dict = {}
    global_var_dict = {}
    tu_dict = {}
    file_cache = {}
    function_info_dict = {}
    item_count_dict = {}  # 记录item被并行使用次数

    # 初始化全局字典
    global_dict_init(root_dir, file_path, function_name, function_info_dict, tu_dict, file_cache, global_type_dict,
                     global_macro_dict, global_var_dict, bc_file_name)

    print('更新全局字典')
    # 更新全局字典
    global_dict_update(function_info_dict, global_type_dict, global_macro_dict, global_var_dict, item_count_dict)

    function_info = function_info_dict[function_name]
    function_code = function_info.code
    fun_var_dict = function_info.fun_var_dict

    print("callee_info_list:\n")
    for callee_info in function_info.callee_info_list:
        print(callee_info.name)

    print("\nmacro_expr_info_list:\n")
    for macro_info in function_info.macro_expr_info_list:
        print(macro_info.name)

    # 调用新的get_callee_context函数
    node_item_map = get_callee_context(function_info.code, function_info.callee_info_list, function_info.macro_expr_info_list)

    print_node_item_map(node_item_map, function_code)

    modifications = record_modified_range_and_content(function_name, function_info_dict, node_item_map, fun_var_dict)
    modifications.extend(record_ret_range_and_content(function_info))
    modifications.extend(record_IP_var_pos(function_info, modifications))


    # # 打印映射关系
    print_modifications(modifications, function_code)
