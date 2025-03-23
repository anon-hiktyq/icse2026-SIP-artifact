import clang.cindex
import sys
import os
from pathlib import Path
import time

clang.cindex.Config.set_library_path('/usr/lib/llvm-18/lib')

import clang.cindex
import os
import sys
import subprocess
import re
import json



def run_clang_mm(source_file, include_args):
    """
    使用 clang -MM 分析源文件的依赖关系。
    """
    # 构造 clang -MM 命令
    command = ['clang', '-MM', source_file] + include_args
    print(command)

    # 执行命令并捕获输出
    try:
        result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, check=True)
        return result.stdout.strip()
    except subprocess.CalledProcessError as e:
        print(f"Error running clang -MM: {e.stderr}")
        return None

def parse_dependency_output(mm_output):
    """
    解析 clang/gcc -MM 的输出，提取所有依赖的头文件路径。
    """
    # 使用正则表达式匹配冒号后面的部分
    match = re.match(r'^\S+:\s*(.*)', mm_output, re.DOTALL)
    if not match:
        return []

    # 获取冒号后面的内容
    headers_str = match.group(1)

    # 去掉多余的空格和反斜杠换行符，然后按空格分割
    headers = []
    current_header = ""
    in_continuation = False  # 标记是否在多行模式中

    for char in headers_str:
        if char == '\\':  # 如果遇到反斜杠，进入多行模式
            in_continuation = True
        elif char == ' ' and not in_continuation:  # 如果遇到空格且不在多行模式中
            if current_header:  # 当前头文件非空时添加到列表
                headers.append(current_header.strip())
                current_header = ""
        else:
            current_header += char  # 添加字符到当前头文件
            in_continuation = False  # 结束多行模式

    # 添加最后一个头文件（如果有的话）
    if current_header:
        headers.append(current_header.strip())
    for header in headers:
        if header == '':
            headers.remove(header)
    # 第一个头文件包含.c文件路径,删去
    new_headers = headers[1:]
    return new_headers

def find_headers_path(root_dir, source_file):

    # 1. 查找所有子目录
    subdirs = [root_dir]
    for dirpath, dirnames, _ in os.walk(root_dir):
        for dirname in dirnames:
            full_path = os.path.join(dirpath, dirname)

            subdirs.append(full_path)

    # 2. 生成 -I 参数
    include_args = []
    for subdir in subdirs:
        include_args.append(f"-I{subdir}")

    # 3. 运行 clang -MM
    output = run_clang_mm(source_file, include_args)
    print(output)

    # 4. 解析依赖信息
    headers = parse_dependency_output(output)

    return headers


def create_tu(file_path, tu_dict, headers = None):
    """
    创建并返回一个 Clang 翻译单元 (Translation Unit)，包括指定的头文件路径。

    :param file_path: 要解析的源文件路径。
    :param tu_dict: 记录所有已经分析过的tu
    :param headers: 包含所有相关头文件路径的列表。
    :return: Clang 翻译单元对象。
    """

    # 如果已经解析过这个文件,直接返回这个tu
    if file_path in tu_dict.keys():
        return tu_dict[file_path]


    index = clang.cindex.Index.create()
    try:
        # 初始化编译选项
        args = [
            '-std=c99',  # 使用 C99 标准
            '-I.',       # 包含当前目录
            '-O0',       # 禁用所有优化
            '-g',        # 生成调试信息
            '-fno-builtin',  # 禁用内置函数优化
            '-Wp,-U__OPTIMIZE__',  # 取消定义优化相关的宏
            # 'LUA_USE_APICHECK'
        ]

        # 将头文件路径转换为 -include 参数并添加到 args 中
        if headers:
            args.extend([f'-include {header}' for header in headers])

        # 解析 C 文件，传递编译选项并使用详细处理记录标志
        tu = index.parse(
            file_path,
            args=args,
            options=clang.cindex.TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD |
                    clang.cindex.TranslationUnit.PARSE_INCOMPLETE
        )

        tu_dict[file_path] = tu
        return tu

    except clang.cindex.TranslationUnitLoadError as e:
        print(f"Error parsing file: {e}")
        sys.exit(1)


def get_item_identifier(name, file_path):
    """生成项目的唯一标识符"""
    return f"{name}@{file_path}"


# 辅助函数：读取文件内容并缓存
def read_file_content(file_path, file_cache):
    if file_path in file_cache:
        return file_cache[file_path]

    try:
        with open(file_path, 'r', encoding="utf-8", errors='replace') as file:
            content = file.read()
            file_cache[file_path] = content
            return content
    except FileNotFoundError as e:
        print(f"File not found: {e}")
        return None


# 辅助函数：获取指针的类型名称
def get_type_name(var_type):
    # if type_cursor.kind == clang.cindex.TypeKind.POINTER:
    #     return f"{get_type_name(type_cursor.get_pointee())}*"
    # elif type_cursor.kind == clang.cindex.TypeKind.TYPEDEF:
    #     return type_cursor.get_canonical().spelling
    # else:
    #     return type_cursor.spelling.split('[')[0]
    # 目前已知的类型表达形式有: char[50], int *, int (const char *, ...), enum Weekday, const char *, struct Person *, union Data等

    """简化掉所有的关键字,*,数组符号"""
    # 忽略有'('的情况:
    if '(' not in var_type:
        #删掉 struct, const, volatile等关键字
        for item in ['struct', 'union', 'enum', 'const', 'volatile']:
            if item in var_type:
                var_type = var_type.replace(item, '')

        #删掉'*'
        var_type = var_type.replace('*','')

        # 删掉'[num]'
        var_type = var_type.split('[')[0].strip()

        # 删掉&
        var_type = var_type.replace('&', '')

        return var_type


def find_function_cursor(tu, function_name, is_definition=True):
    """
    查找指定名称的函数定义或声明。

    :param tu: 翻译单元 (TranslationUnit) 对象。
    :param function_name: 要查找的函数名称。
    :param is_definition: 如果为 True，则查找函数定义；否则查找函数声明或定义。
    :return: 找到的游标 (Cursor)，如果没有找到则返回 None。
    """

    def traverse(node, function_name, is_definition = True):
        """
        递归遍历 AST 并查找指定的函数节点。

        :param node: 当前遍历的 AST 节点。
        :param function_name: 要查找的函数名称。
        :param is_definition: 是否查找函数定义。
        :return: 找到的游标 (Cursor)，如果没有找到则返回 None。
        """
        if node.kind == clang.cindex.CursorKind.FUNCTION_DECL:
            if node.spelling == function_name:
                if is_definition and node.is_definition():
                    return node
                elif not is_definition:
                    print(f'找到函数声明/定义节点{node.spelling}')
                    return node

        # 递归遍历子节点
        for child in node.get_children():
            result = traverse(child, function_name, is_definition)
            if result:
                return result

        return None

    # 从根节点开始遍历
    root_cursor = tu.cursor
    return traverse(root_cursor, function_name, is_definition)

# 辅助函数：判断一个游标是否来自标准库
def is_from_standard_library(cursor):
    if cursor.location.file:
        # 检查文件路径是否包含常见的标准库路径
        standard_library_paths = ['usr/include', 'include/c++', 'include-fixed', '/usr/local/include']
        for path in standard_library_paths:
            if path in cursor.location.file.name:
                return True
    return False

def record_content_range(cursor, offset_line = 1):
    """记录cursor指向内容在原函数中的相对位置"""
    start_line = cursor.extent.start.line - offset_line  # 转换为0的索引
    start_col = cursor.extent.start.column - 1
    end_line = cursor.extent.end.line - offset_line
    end_col = cursor.extent.end.column - 1
    range = (start_line, start_col, end_line, end_col)
    return range

def record_range_content(code, content_range):
    """
    提取源代码中指定范围内的代码
    :param code: 源代码字符串
    :param content_range: 范围列表 [起始行, 起始列, 终止行, 终止列]
    :return: 提取的代码片段
    """
    print(content_range)
    start_line, start_column, end_line, end_column = content_range

    lines = code.splitlines()
    result = []

    # 如果起始行和结束行相同，直接处理这一行
    if start_line == end_line:
        if start_line < len(lines):
            line = lines[start_line]
            result.append(line[start_column:end_column])
        else:
            return "指定的起始或结束行超出源代码范围"
    else:
        # 提取起始行的部分内容
        if start_line < len(lines):
            line = lines[start_line]
            result.append(line[start_column:])
        else:
            return "指定的起始行超出源代码范围"

        # 提取中间的所有完整行
        for i in range(start_line + 1, end_line):
            if i < len(lines):
                result.append(lines[i])
            else:
                return "指定的中间行超出源代码范围"

        # 提取结束行的部分内容
        if end_line < len(lines):
            line = lines[end_line]
            result.append(line[:end_column])
        else:
            return "指定的结束行超出源代码范围"

    return '\n'.join(result)


def read_json_file(file_path):
    try:
        # 打开并读取 JSON 文件
        with open(file_path, 'r', encoding='utf-8') as file:
            # 加载 JSON 数据
            data = json.load(file)
            return data
    except FileNotFoundError:
        print(f"错误：文件 '{file_path}' 未找到。")
    except json.JSONDecodeError as e:
        print(f"错误：JSON 文件格式不正确。详细信息：{e}")
    except Exception as e:
        print(f"发生未知错误：{e}")


def find_c_file_path(root_dir, function_name, tu_dict):
    #先在已有的tu中寻找
    for tu_path in tu_dict:
        for cursor in tu_dict[tu_path].cursor.get_children():
            if cursor.kind == clang.cindex.CursorKind.FUNCTION_DECL and cursor.spelling == function_name:
                # 确保游标对应的是函数定义而非前向声明
                if cursor.is_definition():
                    return cursor.location.file.name

    #如果没找到
    root_path = Path(root_dir)
    # 使用 rglob 递归查找所有 .c 文件
    c_files = [str(file) for file in root_path.rglob("*.c") if not str(file) in tu_dict]
    for c_file in c_files:
        tu = create_tu(c_file, tu_dict)
        tu_dict[c_file] = tu
        for cursor in tu.cursor.get_children():
            if cursor.kind == clang.cindex.CursorKind.FUNCTION_DECL and cursor.spelling == function_name:
                # 确保游标对应的是函数定义而非前向声明
                if cursor.is_definition():
                    return cursor.location.file.name
    # 如果都没找到,返回None
    return None

def remove_comments(code):
    """
    删除代码中的所有注释（包括行注释和块注释），保留字符串字面量中的内容
    
    :param code: 原始代码字符串
    :return: 删除注释后的代码字符串
    """
    result = []
    i = 0
    state = {
        'in_string': False,   # 是否在字符串中
        'in_char': False,     # 是否在字符字面量中
        'escape': False       # 是否是转义字符
    }
    
    def handle_string_char(char):
        """处理字符串和字符字面量中的字符"""
        if char == '\\' and not state['escape']:
            state['escape'] = True
        else:
            state['escape'] = False
        return char
    
    while i < len(code):
        if state['in_string'] or state['in_char']:
            # 处理字符串或字符字面量
            quote = '"' if state['in_string'] else '\''
            if code[i] == quote and not state['escape']:
                state['in_string' if quote == '"' else 'in_char'] = False
            result.append(handle_string_char(code[i]))
            
        else:
            # 处理代码和注释
            if code[i:i+2] == '//':
                # 跳过行注释
                while i < len(code) and code[i] != '\n':
                    i += 1
                if i < len(code):
                    result.append('\n')
                continue
                
            elif code[i:i+2] == '/*':
                # 跳过块注释
                i += 2
                while i < len(code):
                    if code[i-1:i+1] == '*/':
                        i += 1
                        break
                    i += 1
                continue
                
            elif code[i] == '"':
                state['in_string'] = True
                result.append(code[i])
            elif code[i] == '\'':
                state['in_char'] = True
                result.append(code[i])
            elif code[i] == '/' and i + 1 < len(code) and code[i+1] not in ['/', '*']:
                # 只有当/不是注释的开始时才保留
                result.append(code[i])
            else:
                result.append(code[i])
        
        i += 1
    
    # 清理代码格式
    cleaned_code = ''.join(result)
    # 将多个连续空行替换为单个空行
    cleaned_code = re.sub(r'\n\s*\n', '\n\n', cleaned_code)
    # 清理行尾空白
    cleaned_code = re.sub(r'[ \t]+$', '', cleaned_code, flags=re.MULTILINE)
    # 清理可能残留的注释标记
    cleaned_code = re.sub(r'/\*|\*/|//', '', cleaned_code)
    
    return cleaned_code

def clean_temp_files(root_dir):
    """
    删除指定目录中的临时文件（.bc, .o 和 myproject）
    
    :param root_dir: 目标目录路径
    """
    try:
        # 遍历目录
        for item in os.listdir(root_dir):
            item_path = os.path.join(root_dir, item)
            # 检查是否是要删除的文件
            if item.endswith(('.bc', '.o')) or item == 'myproject':
                try:
                    os.remove(item_path)
                    print(f"已删除: {item_path}")
                except Exception as e:
                    print(f"删除 {item_path} 失败: {e}")
    except Exception as e:
        print(f"清理临时文件时发生错误: {e}")

def timer(func):
    """
    装饰器函数，用于计算函数运行时间
    
    :param func: 要计时的函数
    :return: 包装后的函数
    """
    def wrapper(*args, **kwargs):
        start_time = time.time()
        result = func(*args, **kwargs)
        end_time = time.time()
        
        # 计算运行时间
        run_time = end_time - start_time
        
        # 格式化输出
        if run_time < 60:
            print(f"\n程序运行时间: {run_time:.2f} 秒")
        else:
            minutes = int(run_time // 60)
            seconds = run_time % 60
            print(f"\n程序运行时间: {minutes} 分 {seconds:.2f} 秒")
        
        return result
    return wrapper