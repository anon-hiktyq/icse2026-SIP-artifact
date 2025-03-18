from utils import record_content_range, record_range_content, clean_temp_files, remove_comments, timer

from extract_IP_var import extract_IP_var
from extract_all import *
from build_info_dict import *
from parse_function import *
import clang.cindex
from extract_all import create_tu, get_type_name
from operator import itemgetter
from tree_sitter_app import insert_before_identifier
from collections import defaultdict
from main_class import *
import re
from record_callee_range_and_content import record_modified_range_and_content, get_callee_context
import os


def find_function_header_range(code):
    """
    查找指定函数实现部分的头在源代码中的位置。

    :param code: 提取的函数源代码字符串
    :return: 包含起始行、起始列、结束行、结束列的列表 [start_line, start_column, end_line, end_column]，基于0开始计数
    """
    # 函数的起始位置总是code的最开头，因此起始行列为0, 0
    start_line = 0
    start_column = 0

    # 找到第一个出现的 '{' 的位置

    brace_pos = code.find('{')

    if brace_pos == -1:
        raise ValueError("函数体没有找到起始括号 '{'")

    # 计算结束位置的实际行列号
    lines_before_brace = code.count('\n', 0, brace_pos)  # 计算行数
    end_line = lines_before_brace

    if '\n' in code[:brace_pos]:
        last_newline_pos = code.rfind('\n', 0, brace_pos)
        end_column = brace_pos - (last_newline_pos + 1)  # 列数是从上一个换行符之后开始计算，基于0开始
    else:
        end_column = brace_pos  # 如果没有换行符，那么就是从第0列开始计算

    # # 结束位置是 '{' 左边一个单位的位置
    # end_column -= 1

    return [start_line, start_column, end_line, end_column]


def var_dict_update(function_info):
    """由于修改了原函数的返回值,function_info的fun_var_dict和IP_var_dict中的作为返回值的变量,需要做一定的修改"""

    # 从return语句中提取变量名
    ret_vars = set()  # 使用集合存储所有返回的变量名
    for ret_range in function_info.ret_range_list:
        # 获取return语句的内容
        content = record_range_content(function_info.code, ret_range)
        # 去掉return关键字并清理空白
        expr = content.replace('return', '').strip()
        # 如果是单个变量（不包含运算符和函数调用）
        if re.match(r'^[*&]*[a-zA-Z_][a-zA-Z0-9_]*$', expr):
            # 去除指针和引用符号
            var_name = re.sub(r'^[*&]+', '', expr)
            ret_vars.add(var_name)

    # 从IP_var_dict中删除这些变量
    for var in ret_vars:
        for section in ['input', 'output', 'stateVar', 'argVar']:
            if var in function_info.IP_var_dict[section]:
                del function_info.IP_var_dict[section][var]

    # 从fun_var_dict中删除这些变量
    for var in ret_vars:
        if var in function_info.fun_var_dict:
            del function_info.fun_var_dict[var]

    # 添加ret变量到字典中
    ret_type = function_info.func_type
    #当函数是非void函数式,才加入ret变量
    if not ret_type == 'void':
        if not "*" in ret_type:
            ret_type = ret_type + "*"

        # 添加到IP_var_dict的output部分
        function_info.IP_var_dict['output']['ret'] = ret_type

        # 添加到fun_var_dict
        function_info.fun_var_dict['ret'] = ret_type


def find_nearest_insertion_point(code, callee_info):
    """
    找到最近的插入点（分号或左大括号）和缩进信息
    
    :param code: 源代码
    :param callee_info: CalleeInfo对象，包含content_range信息
    :return: 
    - 插入位置 [line, column]
    - 缩进字符串
    """
    lines = code.splitlines()
    cursor_line = callee_info.content_range[0]  # 已经是0索引
    cursor_col = callee_info.content_range[1]   # 已经是0索引

    def get_line_indent(line_content):
        """获取行的实际缩进，忽略注释"""
        # 移除行注释
        line_without_comment = re.sub(r'//.*$', '', line_content)
        # 移除多行注释
        line_without_comment = re.sub(r'/\*.*?\*/', '', line_without_comment)
        # 如果去掉注释后是空行，返回None
        if not line_without_comment.strip():
            return None
        return re.match(r'^\s*', line_without_comment).group()

    # 向上查找最近的分号或左大括号
    current_line = cursor_line
    while current_line >= 0:
        line = lines[current_line]
        search_range = line[:cursor_col] if current_line == cursor_line else line
        
        # 移除注释后再搜索分号或左大括号
        search_range = re.sub(r'//.*$', '', search_range)
        search_range = re.sub(r'/\*.*?\*/', '', search_range)

        # 从右向左查找分号或左大括号
        for i in range(len(search_range) - 1, -1, -1):
            if search_range[i] in [';', '{', ':']:
                # 获取下一行的缩进
                next_line = current_line + 1
                next_indent = "    "  # 默认缩进
                
                # 查找下一个非注释行的缩进
                while next_line < len(lines):
                    indent = get_line_indent(lines[next_line])
                    if indent is not None:
                        next_indent = indent
                        # 如果这行只有右大括号，缩进需要多一级
                        if lines[next_line].strip() == '}':
                            next_indent += "    "
                        break
                    next_line += 1

                return [current_line, i + 1], next_indent #这里返回的位置是找到的{和;后面一格的位置

        current_line -= 1

    return None, "    "  # 默认缩进


def create_ip_expr(callee_name, var_mapping, fun_var_dict, indent=""):
    """将函数体内选定的callee转换为IPCREATE;IPCALL的形式

    形式如:
    IPCREATE(GetUartData, ipGetUartData, .len = 30, .lenAddr = pIp->getLenAddr, .dataAddr = pIp->getDataAddr,.data = &gyroRecvData[0]);
    IPCALL(ipGetUartData);

    :param callee_name: 被调用函数名
    :param var_mapping: 变量映射
    :param fun_var_dict: 函数变量字典
    :param indent: 缩进字符串
    """
    var_list = []
    for key in var_mapping:
        # 如果出现在fun_var_dict,代表该参数包含在IP Struct内
        if get_type_name(key) in fun_var_dict:
            var_list.append(f' .{key} = pIp->{var_mapping[key]}')
        else:
            var_list.append(f' .{key} = {var_mapping[key]}')
    if var_list:
        ip_create_list = [f'IPCREATE({callee_name}', f' ip{callee_name}', ",".join(var_list)]
    else:
        ip_create_list = [f'IPCREATE({callee_name}', f' ip{callee_name}']
    IP_callee_code = (f'{indent}{",".join(ip_create_list)});\n'
                      f'{indent}IPCALL(ip{callee_name});\n')

    return IP_callee_code


def find_var_pos(source_code, fun_var_dict):
    """
    找到所有在 fun_var_dict 中出现的变量的位置。
    会包含变量名前的*和&符号，以及类型转换。
    位置是相对于函数源代码的开始位置。

    :param source_code: 函数源代码字符串
    :param fun_var_dict: 需要修改的变量字典 (key 是变量名)
    :return: 匹配结果列表 [([开始行, 开始列, 结束行, 结束列], "pIp -> ")...]
    """
    result = []
    lines = source_code.splitlines()  # 按行分割源代码

    # 构建正则表达式模式，匹配所有 fun_var_dict 中的变量名及其前面的修饰符
    # 匹配: 
    # 1. 可选的类型转换 ((type*))
    # 2. 可选的指针/引用操作符 (*&)
    # 3. 变量名
    pattern = r'(?:\([^)]+\)\s*)?[*&]*\b(' + '|'.join(re.escape(var) for var in fun_var_dict.keys()) + r')\b'

    # 跳过函数声明部分
    start_line = 0
    for i, line in enumerate(lines):
        if '{' in line:
            start_line = i + 1
            break

    # 遍历每一行，查找变量名
    for line_index, line in enumerate(lines[start_line:], start=start_line):
        # 跳过注释行
        if line.strip().startswith('//') or line.strip().startswith('/*'):
            continue

        # 处理行内注释
        code_line = line
        comment_start = line.find('//')
        if comment_start != -1:
            code_line = line[:comment_start]

        # 查找所有匹配
        for match in re.finditer(pattern, code_line):
            var_start = match.start()  # 包含修饰符的起始位置
            var_end = match.end()  # 变量结束位置

            # 检查是否在字符串中
            in_string = False
            for i, char in enumerate(code_line[:var_start]):
                if char == '"' and (i == 0 or code_line[i-1] != '\\'):
                    in_string = not in_string
            if in_string:
                continue

            # 记录变量位置和替换标记
            result.append(
                ([
                    line_index,  # 开始行（相对于函数开始的位置）
                    var_start,   # 开始列（包含修饰符）
                    line_index,  # 结束行
                    var_start    # 结束列（插入点是变量开始的地方）
                ], "pIp -> ")
            )

    # 按行号和列号排序结果
    result.sort(key=lambda x: (x[0][0], x[0][1]))
    return result


def record_ret_range_and_content(function_info):
    """记录所有return语句的range以及应该替换成的代码"""
    modifications = []
    code = function_info.code
    type = function_info.func_type
    ret_range_list = function_info.ret_range_list
    for ret_range in ret_range_list:
        content = record_range_content(code, ret_range)
        #如果返回的是指针
        if "*" in type:
            content = content.replace("return", "pIp -> ret =")
        else:
            content = content.replace("return", "*(pIp -> ret) =")
        modifications.append((ret_range, content))

    return modifications


def record_modify_place(function_info_dict, function_name):
    """将所有在原函数中需要修改的地方和将最后修改为的代码同时记录在字典中(行数由小到大记录)"""
    modifications = [] #用于存储多个范围及其对应的替换内容

    function_info = function_info_dict[function_name]
    #需要先对function_info的var_dict做处理
    var_dict_update(function_info)

    function_cursor = function_info.function_cursor
    function_start_line = function_cursor.location.line

    # 处理源代码的header:
    header_range = find_function_header_range(function_info.code)
    replace_content = f'void {function_name}Fun(void *p) \n{{'
    modifications.append((header_range, replace_content))

    #处理源代码的IP化的callee:
    print("开始处理IP化的callee")

    node_callee_map = get_callee_context(function_info.function_cursor, function_info.callee_info_list)
    record_modified_range_and_content(modifications, node_callee_map, function_info_dict, function_name,
                                      function_info.fun_var_dict)

    #处理IP函数以外需要加pIp ->部分:
    print("开始处理'pIp ->'")
    if function_info.fun_var_dict:
        modifications.extend(find_var_pos(function_info.code, function_info.fun_var_dict))


    #处理return语句
    print("开始处理return语句")
    if not function_info.func_type == 'void':
        modifications.extend(record_ret_range_and_content(function_info))

    print(modifications)

    return modifications


def apply_modifications(code, modifications):
    """
    根据 modifications 列表对代码进行修改。

    :param code: 原始代码字符串
    :param modifications: 修改列表，形如 [([开始行, 开始列, 结束行, 结束列], 替换内容), ...]
    :return: 修改后的代码字符串
    """
    # 将代码按行分割
    if not modifications:
        return code
    lines = code.splitlines()
    print(f'\n\nmodifications:{modifications}\n')
    # 第一步：按照结束位置从后往前排序
    modifications.sort(key=lambda x: (x[0][2], x[0][3]), reverse=True)

    # 第二步：过滤掉被其他范围包含的 'pIp -> ' 节点
    filtered_modifications = []
    for i, (pos, replacement) in enumerate(modifications):
        start_row, start_col, end_row, end_col = pos

        # 如果替换内容是 'pIp -> '，检查是否被其他范围包含
        if replacement == "pIp -> ":
            is_contained = False
            for j, (other_pos, other_replacement) in enumerate(modifications):
                if i != j and other_replacement != "pIp -> ":  # 排除自身和其他 'pIp -> ' 修改
                    other_start_row, other_start_col, other_end_row, other_end_col = other_pos

                    # 检查当前位置是否在其他修改范围内
                    if (other_start_row < start_row or
                            (other_start_row == start_row and other_start_col <= start_col)):
                        if (other_end_row > start_row or
                                (other_end_row == start_row and other_end_col >= end_col)):
                            is_contained = True
                            break

            if not is_contained:
                filtered_modifications.append((pos, replacement))
        else:
            filtered_modifications.append((pos, replacement))

    # 第三步：按照排序后的顺序依次替换
    for pos, replacement in filtered_modifications:
        start_row, start_col, end_row, end_col = pos

        # # 检查行索引是否有效
        # if start_row >= len(lines) or end_row >= len(lines):
        #     print(f"警告: 行索引超出范围 - 跳过修改 ({start_row}, {end_row})")
        #     continue

        # 处理单行替换
        if start_row == end_row:
            line = lines[start_row]

            # # 检查列索引是否有效
            # if start_col >= len(line):
            #     print(f"警告: 列索引超出范围 - 跳过修改 (行 {start_row}, 列 {start_col})")
            #     continue

            if replacement == "pIp -> ":  # 特殊处理 'pIp -> '
                try:
                    original_char = line[start_col]  # 获取原始字符
                    replacement += original_char  # 将原始字符附加到 'pIp -> ' 后面
                except IndexError:
                    print(f"警告: 无法获取原始字符 (行 {start_row}, 列 {start_col})")
                    continue

            # 安全地执行字符串切片
            new_line = line[:start_col] + replacement
            if end_col + 1 < len(line):
                new_line += line[end_col + 1:]
            lines[start_row] = new_line
        else:
            # 多行替换
            lines[start_row] = lines[start_row][:start_col] + replacement
            for row in range(start_row + 1, end_row):
                lines[row] = ""
            if end_col + 1 < len(lines[end_row]):
                lines[end_row] = lines[end_row][end_col + 1:]
            else:
                lines[end_row] = ""

    # 合并修改后的代码
    return "\n".join(lines)

def create_include_IP_headers(function_info: FunctionInfo):

    include_IP_list = []
    callee_info_list = function_info.callee_info_list
    if callee_info_list:
        for callee_info in callee_info_list:
            if f'#include "{callee_info.name}.h"' not in include_IP_list:
                include_IP_list.append(f'#include "{callee_info.name}.h"')

    return '\n'.join(include_IP_list) + '\n\n'

def create_IP_item(function_info: FunctionInfo, global_type_dict, global_macro_dict, item_count_dict):
    """记录所有该IP非callee相关的类型和宏定义,并根据item_count_dict判断是否添加编译条件"""

    fun_item_dict = function_info.fun_item_dict
    callee_item_set = function_info.callee_item_set
    item_code_list = []
    for item_name in fun_item_dict:

        #当该item不属于callee且不是全局变量时
        if item_name not in callee_item_set and not fun_item_dict[item_name] == 'global':

            #item是宏是
            if fun_item_dict[item_name] == 'macro':
                item_code = f"#define {item_name.split('@')[0]} {global_macro_dict[item_name].def_code}"
            #item是type时
            else:
                item_code = global_type_dict[item_name].def_code
            #当该item未被其他函数使用时
            if item_count_dict[item_name] == 1:
                item_code_list.append(item_code)
            #否则有并行使用的函数,需要添加编译条件
            else:
                item_code_list.append(f'#ifndef _{item_name.upper().split("@")[0]}_\n\t{item_code.replace('\n','\n\t')}\n#endif\n')

    fun_item_code = '\n'.join(item_code_list)
    return fun_item_code

def create_IP_struct(function_name, IP_var_dict, function_info):

    #由于 IP_var_dict的type会有type[]表示数组,需要对这类进行修改
    new_IP_var_dict = {'input': {},'output': {},'stateVar': {},'argVar': {}}
    for var_type in ['input', 'output', 'stateVar', 'argVar']:
        for key in IP_var_dict[var_type]:
            if '[' in IP_var_dict[var_type][key]:
                type_name = IP_var_dict[var_type][key].split('[')[0]
                arr_sign = '[' + '['.join(IP_var_dict[var_type][key].split('[')[1:])
                new_IP_var_dict[var_type][f'{key}{arr_sign}'] = type_name
            else:
                new_IP_var_dict[var_type][key] = IP_var_dict[var_type][key]
    # new_IP_var_dict = {k: v for k, v in dict(new_IP_var_dict).items() if k is not None}
    # print('打印new_IP_var_dict')
    # print(new_IP_var_dict)

    out_in_put = {}
    for key in new_IP_var_dict['input']:
        if key in new_IP_var_dict['output'] and new_IP_var_dict['input'][key] == new_IP_var_dict['output'][key]:
            out_in_put[key] = new_IP_var_dict['output'][key]
            # del new_IP_var_dict['output'][key], new_IP_var_dict['input'][key]
    IP_struct = []
    IP_struct.append(f'void {function_name}Fun(void *p);\n\n'
                     f'typedef struct __{function_name}\n{{\n'
                     f'\t/* Functional Interface */\n\tFun\t\t\tfun;\n'
                     f'\t/* Input Variables */')
    for key in new_IP_var_dict['input']:
        if key not in out_in_put:
            IP_struct.append(f'\t{new_IP_var_dict["input"][key]}\t\t\t{key};')

    #在输出端口,输入输出端口,状态变量中,可能会包含返回值,我们需要将这些返回值全部转换为指针形式
    def trans_to_point(var_dict, ret_dict):
        for var in var_dict:
            if var in ret_dict:
                if not ret_dict[var]:
                    var_dict[var] = var_dict[var] + '*'
        return var_dict

    new_IP_var_dict["output"] = trans_to_point(new_IP_var_dict["output"], function_info.ret_range_list)
    out_in_put = trans_to_point(out_in_put, function_info.ret_range_list)
    new_IP_var_dict["stateVar"] = trans_to_point(new_IP_var_dict["stateVar"], function_info.ret_range_list)

    IP_struct.append('\t/* Output Variables */')
    for key in new_IP_var_dict['output']:
        if key not in out_in_put:
            IP_struct.append(f'\t{new_IP_var_dict["output"][key]}\t\t\t{key};')

    IP_struct.append('\t/* In&Output Variables */')
    for key in out_in_put:
        IP_struct.append(f'\t{out_in_put[key]}\t\t\t{key};')

    IP_struct.append('\t/* Statement Variables*/')
    for key in new_IP_var_dict['stateVar']:
        IP_struct.append(f'\t{new_IP_var_dict["stateVar"][key]}\t\t\t{key};')

    IP_struct.append('\t/* Argument Variables */')
    for key in new_IP_var_dict['argVar']:
        IP_struct.append(f'\t{new_IP_var_dict["argVar"][key]}\t\t\t{key};')

    IP_struct.append(f'}} {function_name};')

    return '\n'.join(IP_struct)


def write_IP_to_h(function_name, IP_struct, IP_item_code, include_IP_headers):
    """

    """

    # 确保输出目录存在
    output_dir = "../Output"
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    # 构建文件路径
    file_path = f"../Output/{function_name}.h"
    with open(file_path, 'w') as file:

        file.write(f'#if !defined(__{function_name.upper()}_H__)\n'
                   f'#define __{function_name.upper()}_H__\n\n')

        file.write('#include "common.h"\n')  # 公共组件
        file.write(include_IP_headers)  #相关IP头文件
        # 写入非callee相关item
        file.write(f'{IP_item_code}\n')
        # 写入创建的函数参数结构体
        file.write(f'\n{IP_struct}\n')
        #写入IP函数声明
        # file.write(f'void {function_name}Fun(void *p);\n\n')

        file.write(f'\n#endif // __{function_name.upper()}_H__')

    print(f"Successfully wrote {file_path}")


def insert_pIp_declaration(code, function_name, function_info):
    """
    在函数体 { 的下一行插入 pIp 声明语句，并删除所有 return 语句。

    :param code: 原始代码字符串
    :param function_name: 函数名称
    :return: 修改后的代码字符串
    """

    # 将代码按行分割
    lines = code.splitlines()

    # 查找函数体开始位置（即 '{' 所在行）
    start_brace_index = None
    for i, line in enumerate(lines):
        if "{" in line.strip() and not line.strip().startswith("//"):
            # 找到函数体开始的 '{'
            start_brace_index = i
            break
    if start_brace_index is None:
        raise ValueError("无法找到函数体开始的 '{'")

    # 构造插入的声明语句
    declaration = f"    {function_name} *pIp = ({function_name}*)p;"

    # 插入声明语句并在删除 return 语句后重新构建代码
    modified_lines = []
    inserted_declaration = False
    for i, line in enumerate(lines):
        # 删除 return 语句
        # if "return" in line.strip() and line.strip().endswith(";"):
        #     for key in function_info.ret_range_list:
        #         if function_info.ret_range_list[key]:
        #             new_line = line.replace("return", f'{key} =&')
        #         else:
        #             new_line = line.replace("return", f'{key} =')
        #     continue

        # 插入 pIp 声明语句
        if i == start_brace_index + 1 and not inserted_declaration:
            modified_lines.append(declaration)
            inserted_declaration = True

        modified_lines.append(line)

    # 合并修改后的代码
    return "\n".join(modified_lines)


def create_c_file(code, function_name):
    # 删除注释
    # cleaned_code = remove_comments(code)

    # 构建文件路径
    file_path = f"../Output/{function_name}.c"
    with open(file_path, 'w') as file:
        file.write(f'#include "{function_name}.h"\n')
        file.write(code)

def remove_volatile(code):
    cleaned_code = re.sub(r'\bvolatile \b', '', code)
    return cleaned_code

def create_common_file(function_info_dict, function_name, root_dir):
    """创建common.h文件，包含所有需要的头文件和宏定义"""
    
    # 创建输出目录
    os.makedirs('../Output', exist_ok=True)
    
    # 收集所有函数中使用的头文件
    all_headers = set()
    for func_info in function_info_dict.values():
        if hasattr(func_info, 'path') and func_info.path:
            # 提取文件所在目录
            file_dir = os.path.dirname(func_info.path)
            # 添加相对路径的头文件
            all_headers.add(f'#include "{os.path.basename(func_info.path)}"')
    
    # 扫描根目录中的所有.c和.h文件，查找库头文件引用
    library_headers = set()
    
    def scan_file_for_headers(file_path):
        try:
            with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
                
            # 使用正则表达式查找所有的 #include <...> 格式的头文件引用
            # 这种格式通常用于标准库或系统头文件
            lib_headers = re.findall(r'#include\s*<([^>]+)>', content)
            for header in lib_headers:
                library_headers.add(f'#include <{header}>')
                
        except Exception as e:
            print(f"扫描文件 {file_path} 时出错: {e}")
    
    # 递归扫描根目录中的所有.c和.h文件
    for root, dirs, files in os.walk(root_dir):
        for file in files:
            if file.endswith(('.c', '.h')):
                scan_file_for_headers(os.path.join(root, file))
    
    # 写入common.h文件
    with open('../Output/common.h', 'w') as f:
        f.write('#ifndef COMMON_H\n')
        f.write('#define COMMON_H\n\n')
        
        # 写入库头文件引用
        f.write('/* standard library */\n')
        for header in sorted(library_headers):
            f.write(f'{header}\n')
        f.write('\n')

        f.write('\ntypedef void (*Fun)(void *);\n')
        f.write('#define IPCALL(IpName, InstName, ...) {IpName InstName = {.fun = IpName##Fun, __VA_ARGS__ };(InstName.fun(&InstName));}\n')

        
        f.write('\n#endif /* COMMON_H */\n')
    
    print(f"Created common.h file, containing {len(library_headers)} library headers and {len(all_headers)} project headers")


def create_IP_file(function_info_dict, function_name, global_type_dict, global_macro_dict, item_count_dict):
    """对所有需要IP化的函数进行处理,生成相应的.c和.h文件"""
    
    processed_functions = []
    
    for func_name, func_info in function_info_dict.items():
        # 只处理需要IP化的函数
        
        # 处理当前函数
        print(f'Start to process {func_name}')
        print(f'{function_info_dict[func_name].code}')
        print(f'{function_info_dict[func_name].path}')
        modifications = record_modify_place(function_info_dict, func_name)
        modify_code = apply_modifications(func_info.code, modifications)
        modify_code = insert_pIp_declaration(modify_code, func_name, func_info)
        create_c_file(modify_code, func_name)
        
        include_IP_headers = create_include_IP_headers(func_info)
        IP_item_code = create_IP_item(func_info, global_type_dict, global_macro_dict, item_count_dict)
        IP_struct = create_IP_struct(func_name, func_info.IP_var_dict, func_info)
        IP_struct = remove_volatile(IP_struct)
        write_IP_to_h(func_name, IP_struct, IP_item_code, include_IP_headers)
        
        processed_functions.append(func_name)
    
    print(f"processed_functions: {', '.join(processed_functions)}")

# @timer
# def process_ip_conversion(file_path, function_name):
#     """
#     处理IP转换的主函数
#     """
#     root_dir = '/'.join(file_path.split('/')[:-1])
#     function_info_dict = {}
#     tu_dict = {}
#
#     create_IP_file(function_info_dict, function_name, global_type_dict, global_macro_dict, item_count_dict,
#                    )
#
#     create_common_file(function_info_dict, function_name)
#
#     clean_temp_files(root_dir)

    # file_path = '../Input/lua/lzio.c'
    # root_dir = '../Input/lua'
    # function_name = 'luaZ_fill'
    # bc_file_name = 'lua'

    # file_path = '../Input/lua/ldo.c'
    # root_dir = '../Input/lua'
    # function_name = 'luaD_pretailcall'
    # bc_file_name = 'lua'

    # file_path = '../Input/lua/ldo.c'
    # root_dir = '../Input/lua'
    # function_name = 'luaD_seterrorobj'
    # bc_file_name = 'lua'

    # file_path = '../Input/lua/lstring.c'
    # root_dir = '../Input/lua'
    # function_name = 'internshrstr'
    # bc_file_name = 'lua'             #debug:当顶层出现函数调用,此时上下文为none,会将none传回

    # file_path = '../Input/lua/lgc.c'
    # root_dir = '../Input/lua'
    # function_name = 'sweeplist'
    # bc_file_name = 'lua'  # debug:当顶层出现函数调用,此时上下文为none,会将none传回

    # file_path = '../Input/lua/ldo.c'
    # root_dir = '../Input/lua'
    # function_name = 'stackinuse'
    # bc_file_name = 'lua'  # debug:当顶层出现函数调用,此时上下文为none,会将none传回




    #
    # file_path = '../Input/lua/lua.c'
    # root_dir = '../Input/lua'
    # function_name = 'main'
    # bc_file_name = 'lua'  # debug:当顶层出现函数调用,此时上下文为none,会将none传回

    # file_path = '../Input/lua/ldo.c'
    # root_dir = '../Input/lua'
    # function_name = 'luaD_seterrorobj'
    # bc_file_name = 'lua'  # debug:当顶层出现函数调用,此时上下文为none,会将none传回


    # file_path = '../Input/test19/test.c'
    # root_dir = '../Input/test19'
    # function_name = 'main'
    # bc_file_name = 'myproject'

    # file_path = '../Input/SAMCode_V1.01/g4eapp.c'
    # root_dir = '../Input/SAMCode_V1.01'
    # function_name = 'main'
    # bc_file_name = 'myproject'

@timer
def app(file_path, root_dir, function_name, bc_file_name):

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

    for function_info in function_info_dict.values():
        remove_macro_expr_callee(function_info.callee_info_list, function_info.macro_expr_info_list)

    #test create_IP_item
    fun_item_code = create_IP_item(function_info_dict[function_name], global_type_dict, global_macro_dict, item_count_dict)
    print(f"主函数item code:\n{fun_item_code}\n")
    create_IP_file(function_info_dict, function_name, global_type_dict, global_macro_dict, item_count_dict)
    create_common_file(function_info_dict, function_name, root_dir)
    clean_temp_files(root_dir)

if __name__ == '__main__':

    file_path = '../Input/lua/llex.c'
    root_dir = '../Input/lua'
    function_name = 'save'
    bc_file_name = 'lua'  # debug:当顶层出现函数调用,此时上下文为none,会将none传回
    #
    # file_path = '../Input/lua/lua.c'
    # root_dir = '../Input/lua'
    # function_name = 'msghandler'
    # bc_file_name = 'lua'  # debug:当顶层出现函数调用,此时上下文为none,会将none传回

    # file_path = '../Input/lua/loadlib.c'
    # root_dir = '../Input/lua'
    # function_name = 'lsys_load'
    # bc_file_name = 'lua'  # debug:当顶层出现函数调用,此时上下文为none,会将none传回

    # file_path = '../Input/SAMCode_V1.01/g4eapp.c'
    # root_dir = '../Input/SAMCode_V1.01'
    # function_name = 'main'
    # bc_file_name = 'myproject'


    app(file_path, root_dir, function_name, bc_file_name)