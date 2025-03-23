# from clang.cindex import Index, CursorKind
from build_info_dict import *
from parse_function import *
from extract_all import create_tu, get_type_name
import tree_sitter_c as tspython
from tree_sitter import Language, Parser
import re

# 初始化 tree-sitter
C_LANGUAGE = Language(tspython.language())
parser = Parser(C_LANGUAGE)

def get_callee_context(function_cursor, callee_info_list):
    """
    获取函数中所有被调用函数的上下文信息
    
    :param function_cursor: 函数的cursor
    :param callee_info_list: 被调用函数的信息列表
    :return: 节点与被调用函数的映射字典 node_callee_map
    """
    node_callee_map = {}
    function_start_line = function_cursor.extent.start.line
    
    # 创建一个映射，将expr_cursor映射到callee_info
    expr_cursor_to_callee = {callee.expr_cursor: callee for callee in callee_info_list}
    
    # 使用迭代方法替代递归，避免递归深度过大
    def get_callee_context_iterative():
        # 使用栈来模拟递归
        # 为函数创建一个默认的COMPOUND_STMT上下文
        default_compound = ("COMPOUND_STMT", record_content_range(function_cursor, function_start_line))
        stack = [(function_cursor, default_compound, False)]  # (cursor, current_context, in_control_body)
        visited = set()  # 记录已访问的节点，避免循环
        
        while stack:
            cursor, current_context, in_control_body = stack.pop()
            
            # 避免重复处理同一个节点
            cursor_id = str(cursor.hash)
            if cursor_id in visited:
                continue
            visited.add(cursor_id)
            
            # 获取当前节点的类型和范围
            node_context = None
            try:
                if cursor.kind == clang.cindex.CursorKind.COMPOUND_STMT:
                    node_context = ("COMPOUND_STMT", record_content_range(cursor, function_start_line))
                    # 复合语句会更新当前上下文
                    current_context = node_context
                elif cursor.kind == clang.cindex.CursorKind.IF_STMT:
                    node_context = ("IF_STMT", record_content_range(cursor, function_start_line))
                    # 条件判断会更新当前上下文
                    current_context = node_context
                elif cursor.kind == clang.cindex.CursorKind.SWITCH_STMT:
                    node_context = ("SWITCH_STMT", record_content_range(cursor, function_start_line))
                    # 条件判断会更新当前上下文
                    current_context = node_context
                elif cursor.kind == clang.cindex.CursorKind.CASE_STMT:
                    node_context = ("CASE_STMT", record_content_range(cursor, function_start_line))
                    # CASE语句会更新当前上下文
                    current_context = node_context
                elif cursor.kind == clang.cindex.CursorKind.DEFAULT_STMT:
                    node_context = ("DEFAULT_STMT", record_content_range(cursor, function_start_line))
                    # DEFAULT语句会更新当前上下文
                    current_context = node_context
                elif cursor.kind in [clang.cindex.CursorKind.WHILE_STMT, 
                                    clang.cindex.CursorKind.FOR_STMT, 
                                    clang.cindex.CursorKind.DO_STMT]:
                    node_context = ("LOOP_STMT", record_content_range(cursor, function_start_line))
                    # 循环会更新当前上下文
                    current_context = node_context
                elif cursor.kind == clang.cindex.CursorKind.RETURN_STMT:
                    node_context = ("RETURN_STMT", record_content_range(cursor, function_start_line))
                    # 如果当前上下文是COMPOUND_STMT，则更新上下文
                    if current_context and current_context[0] == "COMPOUND_STMT":
                        current_context = node_context
                elif cursor.kind in [clang.cindex.CursorKind.VAR_DECL, clang.cindex.CursorKind.FUNCTION_DECL]:
                    node_context = ("DECL_STMT", record_content_range(cursor, function_start_line))
                    # 如果当前上下文是COMPOUND_STMT，则更新上下文
                    if current_context and current_context[0] == "COMPOUND_STMT":
                        current_context = node_context
                elif cursor.kind in [clang.cindex.CursorKind.BINARY_OPERATOR, 
                                    clang.cindex.CursorKind.UNARY_OPERATOR,
                                    clang.cindex.CursorKind.CONDITIONAL_OPERATOR]:
                    node_context = ("EXPR_STMT", record_content_range(cursor, function_start_line))
                    # 如果当前上下文是COMPOUND_STMT，则更新上下文
                    if current_context and current_context[0] == "COMPOUND_STMT":
                        current_context = node_context
                elif cursor.kind == clang.cindex.CursorKind.CALL_EXPR:
                    node_context = ("CALL_STMT", record_content_range(cursor, function_start_line))
            except Exception as e:
                print(f"Error getting node context for {cursor.kind}: {e}")
                continue
            
            # 如果是函数调用表达式，检查是否在callee_info_list中
            if cursor.kind == clang.cindex.CursorKind.CALL_EXPR and cursor in expr_cursor_to_callee:
                callee_info = expr_cursor_to_callee[cursor]
                
                # 判断是否在条件表达式中
                is_in_condition = False
                parent = cursor.semantic_parent
                while parent and parent != function_cursor:
                    if parent.kind in [clang.cindex.CursorKind.IF_STMT, 
                                      clang.cindex.CursorKind.SWITCH_STMT,
                                      clang.cindex.CursorKind.WHILE_STMT,
                                      clang.cindex.CursorKind.FOR_STMT,
                                      clang.cindex.CursorKind.DO_STMT]:
                        # 检查是否在条件部分
                        condition_children = list(parent.get_children())
                        if len(condition_children) > 0 and condition_children[0] != cursor:
                            for child in condition_children:
                                if child.kind == clang.cindex.CursorKind.COMPOUND_STMT:
                                    break
                                if cursor in list(child.get_tokens()):
                                    is_in_condition = True
                                    break
                    parent = parent.semantic_parent
                
                # 根据上下文规则确定使用哪个上下文
                if is_in_condition:
                    # 如果在条件表达式中，使用当前上下文
                    node_callee_map[current_context] = callee_info
                elif in_control_body:
                    # 如果在没有{}的控制语句体内，使用当前节点作为上下文
                    node_callee_map[node_context] = callee_info
                elif current_context and current_context[0] == "COMPOUND_STMT":
                    # 如果当前上下文是COMPOUND_STMT，使用当前的CALL_STMT作为上下文
                    node_callee_map[node_context] = callee_info
                elif current_context and current_context[0] in ["DECL_STMT", "EXPR_STMT", "RETURN_STMT"]:
                    # 如果当前上下文是DECL, EXPR, RETURN，使用当前上下文
                    node_callee_map[current_context] = callee_info
                else:
                    # 其他情况使用当前上下文
                    node_callee_map[current_context] = callee_info
            
            # 处理控制语句
            is_control_stmt = cursor.kind in [
                clang.cindex.CursorKind.IF_STMT,
                clang.cindex.CursorKind.SWITCH_STMT,
                clang.cindex.CursorKind.WHILE_STMT,
                clang.cindex.CursorKind.FOR_STMT,
                clang.cindex.CursorKind.DO_STMT,
            ]
            
            # 处理CASE和DEFAULT语句
            is_case_or_default = cursor.kind in [
                clang.cindex.CursorKind.CASE_STMT,
                clang.cindex.CursorKind.DEFAULT_STMT,
            ]
            
            if is_control_stmt:
                try:
                    # 找到控制语句的条件部分和语句体
                    children = list(cursor.get_children())
                    condition = None
                    body = None
                    
                    for child in children:
                        if child.kind == clang.cindex.CursorKind.COMPOUND_STMT:
                            body = child
                            break
                        elif condition is None:
                            condition = child
                        else:
                            body = child
                    
                    # 处理条件部分
                    if condition:
                        stack.append((condition, current_context, False))
                    
                    # 处理语句体
                    if body:
                        # 如果语句体不是复合语句，创建新的上下文
                        if body.kind != clang.cindex.CursorKind.COMPOUND_STMT:
                            # 对于没有{}的控制语句体，创建虚拟的COMPOUND_STMT上下文
                            virtual_compound = ("COMPOUND_STMT", record_content_range(body, function_start_line))
                            stack.append((body, virtual_compound, True))
                        else:
                            # 如果是复合语句，处理其子节点
                            stack.append((body, node_context, False))
                except Exception as e:
                    print(f"Error processing control statement: {e}")
                continue
            
            # 处理CASE和DEFAULT语句
            elif is_case_or_default:
                try:
                    # CASE语句的第一个子节点是条件表达式，后面的子节点是语句体
                    # DEFAULT语句只有语句体
                    children = list(cursor.get_children())
                    
                    # 跳过CASE语句的条件表达式
                    start_idx = 1 if cursor.kind == clang.cindex.CursorKind.CASE_STMT else 0
                    
                    # 处理语句体
                    for i in range(start_idx, len(children)):
                        child = children[i]
                        if child.kind == clang.cindex.CursorKind.COMPOUND_STMT:
                            # 如果是复合语句，直接处理
                            stack.append((child, node_context, False))
                        else:
                            # 如果不是复合语句，创建虚拟的COMPOUND_STMT上下文
                            virtual_compound = ("COMPOUND_STMT", record_content_range(child, function_start_line))
                            stack.append((child, virtual_compound, True))
                except Exception as e:
                    print(f"Error processing case/default statement: {e}")
                continue
            
            # 处理子节点
            try:
                for child in cursor.get_children():
                    stack.append((child, current_context, in_control_body))
            except Exception as e:
                print(f"Error processing children: {e}")
    
    # 使用迭代方法处理
    get_callee_context_iterative()
    
    # 过滤掉所有None的键值对
    filtered_node_callee_map = {k: v for k, v in node_callee_map.items() if k is not None and k[0] is not None and k[1] is not None}
    
    return filtered_node_callee_map


def create_ip_expr(callee_info, fun_var_dict, ip_call_code_list, ret_def_dict, function_info_dict, ret_count, callee_rank_dict):
    """
    将函数体内选定的callee转换为IPCALL的形式
    形式如:
    IPCALL(GetUartData, ipGetUartData, .len = 30, .lenAddr = pIp->getLenAddr, .dataAddr = pIp->getDataAddr,.data = &gyroRecvData[0]);
    """

    # 处理子函数
    if callee_info.sub_function_info_list:
        for sub_function_info in callee_info.sub_function_info_list:
            create_ip_expr(sub_function_info, fun_var_dict, ip_call_code_list, ret_def_dict, function_info_dict, ret_count, callee_rank_dict)

    var_mapping = callee_info.var_mapping
    var_list = []

    # 获取函数类型
    func_type = function_info_dict[callee_info.name].func_type

    # 为非void函数添加ret
    if func_type != 'void':
        ret_name = f'{callee_info.name}_ret_{ret_count}'
        is_pointer = '*' in func_type
        ret_def = f'{func_type} {ret_name};'
        ret_def_dict[ret_name] = {'secondary_range': callee_info.content_range, 'ret_type': func_type}

        # 添加到var_mapping
        var_mapping['ret'] = {'arg': f'{"&" if not is_pointer else ""}{ret_name}', 'type': 'variable'}

        # 将ret_def添加到IPCALL代码列表
        ip_call_code_list.append(f'{ret_def}')

        # 增加ret计数
        ret_count += 1

    # 计算callee_rank
    if callee_info.name not in callee_rank_dict:
        callee_rank_dict[callee_info.name] = 0
    callee_rank = callee_rank_dict[callee_info.name]
    callee_rank_dict[callee_info.name] += 1

    # 处理var_mapping中的参数
    for key, arg_info in var_mapping.items():
        if arg_info['type'] == 'function':
            # 查找对应的子函数
            for sub_function in callee_info.sub_function_info_list:
                if sub_function.body in arg_info['arg']:
                    for ret_name in ret_def_dict:
                        if ret_def_dict[ret_name]['secondary_range'] == sub_function.content_range:
                            arg_info['arg'] = arg_info['arg'].replace(sub_function.body, ret_name)
                            break

        # 如果出现在fun_var_dict,代表该参数包含在IP Struct内
        if get_type_name(key) in fun_var_dict:
            var_list.append(f'.{key} = pIp->{arg_info["arg"]}')
        else:
            var_list.append(f'.{key} = {arg_info["arg"]}')

    # 生成IPCALL语句
    if var_list:
        ip_call = ','.join([f'IPCALL({callee_info.name}', f'ip{callee_info.name}_{callee_rank}', ",".join(var_list)]) + ');'
    else:
        ip_call = ','.join(
            [f'IPCALL({callee_info.name}', f'ip{callee_info.name}_{callee_rank}']) + ');'
    ip_call_code_list.append(ip_call)

    return ret_count


def extract_condition_range_and_content(code):
    """
    使用 tree-sitter 提取条件判断语句中的条件部分
    :param code: 源代码
    :return: 条件部分的范围和内容
    """
    tree = parser.parse(bytes(code, "utf8"))
    root_node = tree.root_node
    
    # 使用集合记录已访问的节点ID
    visited = set()
    
    # 遍历 AST 找到对应的条件节点
    def find_condition_node(node):
        # 避免重复处理同一个节点
        node_id = id(node)
        if node_id in visited:
            return None
        visited.add(node_id)
        
        if node.type in ['if_statement', 'switch_statement']:
            for child in node.children:
                if child.type == 'parenthesized_expression':
                    return child
        
        # 递归处理子节点
        for child in node.children:
            result = find_condition_node(child)
            if result:
                return result
        
        return None
    
    # 使用迭代方法替代递归，避免栈溢出
    def find_condition_node_iterative(root):
        stack = [root]
        visited = set()
        
        while stack:
            node = stack.pop()
            
            # 避免重复处理
            node_id = id(node)
            if node_id in visited:
                continue
            visited.add(node_id)
            
            # 检查当前节点
            if node.type in ['if_statement', 'switch_statement']:
                for child in node.children:
                    if child.type == 'parenthesized_expression':
                        return child
            
            # 将子节点加入栈中
            for child in reversed(node.children):  # 反转顺序以保持DFS顺序
                stack.append(child)
        
        return None
    
    # 使用迭代方法查找条件节点
    condition_node = find_condition_node_iterative(root_node)
    
    if condition_node:
        start_line, start_col = condition_node.start_point
        end_line, end_col = condition_node.end_point
        return (start_line, start_col, end_line, end_col)
    
    return None  # 如果没有找到条件节点，返回None

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
            pattern = r'\b' + var_name + r'\b'
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
                pattern = r'\b' + var_name + r'\b'
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
            pattern = r'\b' + var_name + r'\b'
            segment = re.sub(pattern, f'pIp->{var_name}', segment)
        result.append(segment)
    
    return ''.join(result)

def record_modified_range_and_content(modifications, node_callee_map, function_info_dict, function_name, fun_var_dict):
    """
    记录需要修改的内容和范围到modifications中
    :param modifications: 记录修改的列表
    :param node_callee_map: 节点与被调用函数的映射字典
    :param function_info_dict: 函数信息字典
    :param function_name: 当前处理的函数名称
    :param fun_var_dict: 函数变量字典
    """
    code = function_info_dict[function_name].code
    ret_count = 0
    callee_rank_dict = {}

    # 整合 node_callee_map 中的 callee
    print(f'现在要处理的node_callee_map:\n    key:{node_callee_map.keys()}')
    # 首先去除所有为None的node_callee_map.items
    new_node_callee_map = {}
    #会有(node_type, first_range)为None的情况,需要排除这部分键值对
    
    for (node_type, node_range), callee in node_callee_map.items():
        if node_type in ['CALL_STMT', 'EXPR_STMT', 'DECL_STMT']:
            ip_call_code_list = []
            ret_def_dict = {}

            # 处理所有出现在该范围的 callee
            for (inner_node_type, inner_node_range), inner_callee in node_callee_map.items():
                if inner_node_range == node_range:
                    ret_count = create_ip_expr(inner_callee, fun_var_dict, ip_call_code_list, ret_def_dict, function_info_dict, ret_count, callee_rank_dict)

            if node_type == 'CALL_STMT':
                # 处理单独的语句情况
                modified_content = '{' + ''.join(ip_call_code_list) + '}'
                # 替换变量为IP结构体形式
                modified_content = replace_var_with_ip_struct(modified_content, fun_var_dict)
                modifications.append((node_range, modified_content))

            elif node_type == 'EXPR_STMT':
                # 处理表达式中的函数调用
                original_content = record_range_content(code, node_range)

                for ret_name in ret_def_dict:
                    if ret_def_dict[ret_name]['secondary_range'] == callee.content_range:
                        original_content = original_content.replace(record_range_content(code, callee.content_range), ret_name)
                        break

                modified_content = '{' + ''.join(ip_call_code_list) + original_content + ';}'
                # 替换变量为IP结构体形式
                modified_content = replace_var_with_ip_struct(modified_content, fun_var_dict)
                modifications.append((node_range, modified_content))

            elif node_type == 'DECL_STMT':
                # 处理变量声明中的函数调用
                original_content = record_range_content(code, node_range)

                # 替换函数调用为ret_name
                for ret_name in ret_def_dict:
                    if ret_def_dict[ret_name]['secondary_range'] == callee.content_range:
                        original_content = original_content.replace(record_range_content(code, callee.content_range), ret_name)
                        break

                # 拆分声明和赋值
                print(f"现在处理的DECL_STMT语句为{original_content}")
                decl_content = original_content.split('=')[0].strip() + ';'
                decl_name = decl_content.split(' ')[-1][:-1]
                assign_content = decl_name + ' = ' + original_content.split('=')[1].strip()

                # 生成新的代码块
                modified_content = decl_content + '{' + ''.join(ip_call_code_list) + assign_content + '}'
                # 替换变量为IP结构体形式
                modified_content = replace_var_with_ip_struct(modified_content, fun_var_dict)
                modifications.append((node_range, modified_content))

        elif node_type in ['IF_STMT', 'SWITCH_STMT']:
            # 处理条件判断语句中的函数调用
            ip_call_code_list = []
            ret_def_dict = {}

            # 处理所有出现在该范围的 callee
            for (inner_node_type, inner_node_range), inner_callee in node_callee_map.items():
                if inner_node_range == node_range:
                    ret_count = create_ip_expr(inner_callee, fun_var_dict, ip_call_code_list, ret_def_dict, function_info_dict, ret_count, callee_rank_dict)

            # 使用 tree-sitter 提取条件部分
            condition_range = extract_condition_range_and_content(code)

            # 替换函数调用为ret_name
            for ret_name in ret_def_dict:   
                if ret_def_dict[ret_name]['secondary_range'] == callee.content_range:
                    # 将替换的内容和范围存入 modifications
                    modifications.append((callee.content_range, f'({ret_name})'))
                    break

            # 生成新的代码块
            ip_call_code_list.insert(0, '{')
            modified_content = ''.join(ip_call_code_list) + record_range_content(code, node_range)[0]
            # 替换变量为IP结构体形式
            modified_content = replace_var_with_ip_struct(modified_content, fun_var_dict)

            # 插入修改
            modifications.append(((node_range[0], node_range[1], node_range[0], node_range[1]), modified_content))

            # 在整个if语句的结尾加上'}'
            modifications.append(((node_range[2], node_range[3], node_range[2], node_range[3]), '}'))


def print_node_callee_map(node_callee_map, function_code):
    """
    打印节点与被调用函数的映射关系
    
    :param node_callee_map: 节点与被调用函数的映射字典
    :param function_code: 函数的源代码
    """
    print("\n=== 节点与被调用函数映射关系 ===\n")
    
    # 按节点类型对映射进行分组
    type_groups = {}
    for (block_type, block_range), callee in node_callee_map.items():
        if block_type not in type_groups:
            type_groups[block_type] = []
        type_groups[block_type].append((block_range, callee))
    
    # 为每种类型打印信息
    for block_type in sorted(type_groups.keys()):
        print(f"\n{block_type}:")
        print("=" * (len(block_type) + 1))
        
        for block_range, callee in type_groups[block_type]:
            # 提取该范围内的代码
            code_snippet = record_range_content(function_code, block_range)
            
            # 打印基本信息
            print(f"\n位置: 第 {block_range[0]+1} 行, 第 {block_range[1]+1} 列 到 第 {block_range[2]+1} 行, 第 {block_range[3]+1} 列")
            print(f"被调用函数: {callee.name}")
            print(f"函数定义文件: {callee.file_path}")
            
            # 打印代码片段
            print("\n代码片段:")
            print("-" * 40)
            print(code_snippet)
            print("-" * 40)
            
            # 打印参数映射
            if callee.var_mapping:
                print("\n参数映射:")
                for param, arg_info in callee.var_mapping.items():
                    print(f"  {param} => {arg_info['arg']} ({arg_info['type']})")
            
            # 打印子函数信息
            if callee.sub_function_info_list:
                print("\n子函数:")
                for sub_func in callee.sub_function_info_list:
                    print(f"  - {sub_func.name}")
            
            print("\n" + "-" * 80 + "\n")

if __name__ == "__main__":
    # file_path = '../Input/SAMCode_V1.01/g4eapp.c'
    # # file_path = '../Input/test7/main.c'
    # root_dir = '../Input/SAMCode_V1.01'
    # bc_file_name = 'myproject'
    # function_name = 'TcProcess'

    # file_path = '../Input/test17/test.c'
    # root_dir = '../Input/test17'
    # function_name = 'main'
    # bc_file_name = 'myproject'

    file_path = '../Input/lua/ldo.c'
    root_dir = '../Input/lua'
    function_name = 'luaD_seterrorobj'
    bc_file_name = 'lua'


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


    print("callee_info_list:\n")
    for callee_info in function_info.callee_info_list:
        print(callee_info.name)
    # 调用新的get_callee_context函数
    node_callee_map = get_callee_context(function_info.function_cursor, function_info.callee_info_list)
    
    # 打印映射关系
    print_node_callee_map(node_callee_map, function_info.code)
