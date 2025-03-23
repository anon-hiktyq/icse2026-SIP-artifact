import clang.cindex
import sys
import os
import re
from utils import create_tu, read_file_content, get_type_name, is_from_standard_library
from config import standard_library_headers
from utils import record_content_range, record_range_content, get_item_identifier, find_function_cursor
from main_class import MacroInfo,TypeInfo, CalleeInfo
from tree_sitter_app import macro_item_update, extract_macro_def_code

clang.cindex.Config.set_library_path('/usr/lib/llvm-18/lib')


def is_has_body(cursor, file_cache):
    """判断一个宏是否含有body"""

    # 获取宏定义所在位置
    extent = cursor.extent

    # 读取整个文件内容
    file_path = cursor.location.file.name

    file_content = read_file_content(file_path,file_cache)

    # 根据宏定义的起始和结束位置提取宏定义的具体内容
    macro_definition = file_content[extent.start.offset:extent.end.offset]

    # 检查宏定义是否只有宏名而没有替换体
    return len(macro_definition.strip().split(None, 1)) > 1

def extract_global_macro(cursor, tu_macro_dict, tu_item_dict, file_cache):
    """
    从宏定义节点中提取信息并更新到tu_macro_dict中
    
    :param cursor: 宏定义的cursor节点
    :param tu_macro_dict: 全局宏信息字典
    :param tu_item_dict: 全局项目字典
    """

    # 忽略来自标准库的宏和不含有body的宏
    if not cursor.location.file or is_from_standard_library(cursor):
        return

    if not is_has_body(cursor, file_cache):
        return

    file_path = cursor.location.file.name if cursor.location.file else None
    if not file_path:
        return
        
    # 生成唯一标识符
    identifier = get_item_identifier(cursor.spelling, file_path)
    
    # 如果该宏已经处理过，直接返回
    if identifier in tu_macro_dict:
        return
    
    # 创建新的MacroInfo对象
    macro_info = MacroInfo(
        file_path=file_path,
        macro_cursor=cursor
    )
    
    
    # 将MacroInfo添加到全局字典中
    tu_macro_dict[identifier] = macro_info
    # print(f"Found macro: {identifier} in {file_path}")
    
    # 记录项目到tu_item_dict，添加flag字段
    tu_item_dict[identifier] = {'kind': 'macro', 'flag': False}


def extract_global_type(node, tu_type_dict, tu_item_dict, file_cache, global_type_dict):
    """
    从类型定义节点中提取信息并更新到tu_type_dict中
    
    :param node: 类型定义的cursor节点
    :param tu_type_dict: 全局类型信息字典
    :param tu_item_dict: 全局项目字典
    """
    # 忽略来自标准库的定义
    if is_from_standard_library(node):
        return
    
    file_path = node.location.file.name if node.location.file else None
    if not file_path:
        return

    # 生成唯一标识符
    identifier = get_item_identifier(get_type_name(node.spelling), file_path)

    # 如果该类型已经处理过，直接返回
    if identifier in tu_type_dict:
        return

    #提取类型的源代码
    filename = node.extent.start.file.name
    code = read_file_content(filename, file_cache)
    content_range = record_content_range(node)
    def_code = record_range_content(code, content_range) + ';'

    # 创建新的TypeInfo对象
    type_info = TypeInfo(
        file_path=file_path,
        content_range=content_range,
        def_code=def_code,
        type_cursor=node
    )

    # 分析类型定义中包含的其他元素
    # 如果已经被分析过,直接从global_type_dict取出
    if identifier in global_type_dict:
        type_info = global_type_dict[identifier]
    else:
        analyze_type_content(node, type_info)
        if type_info.include_item_set and identifier.split('@')[0] in type_info.include_item_set:
            type_info.include_item_set.remove(identifier.split('@')[0]) #去除自身类型

    # 将TypeInfo添加到全局字典中
    tu_type_dict[identifier] = type_info
    # print(f"Found type: {node.spelling} in {file_path}")

    # 记录项目到tu_item_dict，添加flag字段
    tu_item_dict[identifier] = {'kind': 'type', 'flag': False}


def analyze_type_content(node, type_info):
    """
    分析类型定义中包含的其他元素
    
    :param node: 类型定义的cursor节点
    :param type_info: TypeInfo对象
    """

    # 使用get_tokens提取类型定义内容
    tokens = list(node.get_tokens())
    for token in tokens:
        if token.kind == clang.cindex.TokenKind.IDENTIFIER:
            identifier = token.spelling
            
            # 检查是否是类型
            if token.cursor.kind in [clang.cindex.CursorKind.TYPE_REF,
                                      clang.cindex.CursorKind.STRUCT_DECL,
                                      clang.cindex.CursorKind.UNION_DECL,
                                      clang.cindex.CursorKind.ENUM_DECL,
                                      clang.cindex.CursorKind.TYPEDEF_DECL]:
                type_id = get_type_name(identifier)
                type_info.include_item_set.add(type_id)
            
            # 检查是否是宏引用
            elif token.kind == clang.cindex.TokenKind.IDENTIFIER:
                type_info.include_item_set.add(identifier)
            
            # 如果无法确定类型，也将标识符添加到集合中，可能是宏
            elif token.cursor.kind == clang.cindex.CursorKind.UNEXPOSED_EXPR:
                type_info.include_item_set.add(identifier)
                
            # # 检查是否是全局变量
            # elif token.cursor.kind == clang.cindex.CursorKind.VAR_DECL:
            #     type_info.include_global_set.add(identifier)

    # 遍历类型定义的子节点
    for child in node.get_children():
        analyze_type_content(child, type_info)


def extract_global_variable(node, tu_var_dict, tu_item_dict):
    """
    从全局变量节点中提取信息并更新到global_dict中

    :param node: 全局变量的cursor节点
    :param tu_var_dict: 全局变量信息字典
    :param tu_item_dict: 全局项目字典
    """
    # 忽略来自标准库的定义
    if is_from_standard_library(node):
        return

    file_path = node.location.file.name if node.location.file else None
    if not file_path:
        return

    # 生成唯一标识符
    identifier = node.spelling

    # 如果该全局变量已经处理过，直接返回
    if identifier in tu_var_dict:
        return

    # 检查父节点是否为翻译单元
    if node.semantic_parent.kind != clang.cindex.CursorKind.TRANSLATION_UNIT:
        return

    # 记录全局变量的类型
    tu_var_dict[identifier] = get_type_name(node.type.spelling)
    # print(f"Found global variable: {identifier} of type {tu_var_dict[identifier]} in {file_path}")

    # 记录项目到tu_item_dict，添加flag字段
    tu_item_dict[identifier] = {'kind': 'variable', 'flag': False}

    
def parse_file(root_dir, tu, file_cache, global_type_dict, global_macro_dict, global_var_dict):
    """遍历AST，提取所有全局变量,宏,typedef,结构体的定义(及其成员类型)"""

    tu_type_dict = {}   #所有的类型字典
    tu_macro_dict = {}  #所有的宏字典
    tu_var_dict = {}    #所有的全局变量的字典
    tu_item_dict = {}   #保证所有的item顺序正确
    include_file_paths = set()

    def init_file(node, root_dir, tu_type_dict, tu_macro_dict, tu_item_dict, include_file_paths, global_type_dict,
                  global_macro_dict, global_global_dict):
        # 忽略来自标准库的定义
        if not is_from_standard_library(node):
            if node.location.file:
                include_file_paths.add(node.location.file.name)

            # 提取宏
            if node.kind == clang.cindex.CursorKind.MACRO_DEFINITION:
                extract_global_macro(node, tu_macro_dict, tu_item_dict, file_cache)

            # 提取类型
            if node.kind in [clang.cindex.CursorKind.TYPEDEF_DECL,
                              clang.cindex.CursorKind.STRUCT_DECL,
                              clang.cindex.CursorKind.UNION_DECL,
                              clang.cindex.CursorKind.ENUM_DECL]:
                extract_global_type(node, tu_type_dict, tu_item_dict, file_cache, global_type_dict)
                return

            # 提取全局变量
            if node.kind == clang.cindex.CursorKind.VAR_DECL:
                extract_global_variable(node, tu_var_dict, tu_item_dict)

        # 递归遍历子节点
        for child in node.get_children():
            init_file(child, root_dir, tu_type_dict, tu_macro_dict, tu_item_dict, include_file_paths, global_type_dict,
                      global_macro_dict, global_global_dict)

    init_file(tu.cursor, root_dir, tu_type_dict, tu_macro_dict, tu_item_dict, include_file_paths, global_type_dict,
              global_macro_dict, global_var_dict)

    # 对 tu_macro_dict进行update
    # 更新宏信息，提取宏的body.
    for include_file_path in include_file_paths:
        file_code = read_file_content(include_file_path, file_cache)
        extract_macro_def_code(tu_macro_dict, file_code)

    # 对 tu_macro_dict进行update
    # for macro in tu_macro_dict:
    #     # print(macro)
    #     # 如果过不在global_macro_dict,则更新该macro
    #     if not macro in global_macro_dict:
    #         macro_item_update(tu, tu_item_dict, tu_macro_dict[macro], tu_var_dict)

    return  tu_type_dict, tu_macro_dict, tu_var_dict, tu_item_dict


def print_tree(tu_item_dict, tu_macro_dict, tu_type_dict, tu_var_dict, indent=0):
    """
    打印全局项目字典的树形结构

    :param tu_item_dict: 全局项目字典
    :param tu_macro_dict: 全局宏信息字典
    :param tu_type_dict: 全局类型信息字典
    :param tu_var_dict: 全局变量字典
    :param indent: 当前缩进级别
    """
    for identifier, item in tu_item_dict.items():
        kind = item['kind']

        # 打印项目
        print(' ' * indent + f"{kind.capitalize()}: {identifier}")

        # 根据类型打印详细信息
        if kind == 'macro':
            info = tu_macro_dict[identifier]
            print(' ' * (indent + 2) + f"File: {info.file_path}")
            print(' ' * (indent + 2) + f"Macro Code: {info.def_code}")
            print(' ' * (indent + 2) + f"Included Macros: {list(info.include_macro_set)}")
            print(' ' * (indent + 2) + f"Included Types: {list(info.include_item_set)}")
            print(' ' * (indent + 2) + f"Included Globals: {list(info.include_global_set)}")

            # 打印宏表达式信息
            if info.macro_expr_info_list:
                for macro_expr in info.macro_expr_info_list:
                    print(' ' * (indent + 2) + f"Macro Expression: {macro_expr.name}")
                    print(' ' * (indent + 4) + f"Body: {macro_expr.body}")
                    print(' ' * (indent + 4) + f"Origin Content Range: {macro_expr.content_range}")

                    # 打印子函数信息
                    for sub_function in macro_expr.sub_function_info_list:
                        print(' ' * (indent + 6) + f"Sub Function: {sub_function.name}")
                        print(' ' * (indent + 6) + f"Body: {sub_function.body}")
                        print(' ' * (indent + 6) + f"Content Range: {sub_function.content_range}")
                        print(' ' * (indent + 6) + f"Variable Mapping: {sub_function.var_mapping}")
            else:
                print(' ' * (indent + 2) + f"Not macro_expr_info_list:")

        elif kind == 'type':
            info = tu_type_dict[identifier]
            print(' ' * (indent + 2) + f"File: {info.file_path}")
            print(' ' * (indent + 2) + f"Content Range: {info.content_range}")
            print(' ' * (indent + 2) + f"Included Types: {list(info.include_item_set)}")

        elif kind == 'variable':
            print(' ' * (indent + 2) + f"Type: {tu_var_dict[identifier]}")

if __name__ == "__main__":

    # 缓存已读取的文件内容

    # file_path = '../Input/test7/main.c'
    # root_dir = '../Input/test7'

    # file_path = '../Input/SAMCode_V1.01/g4eapp.c'
    # root_dir = '../Input/SAMCode_V1.01'

    file_path = '../Input/test16/test.c'
    root_dir = '../Input/test16'
    function_name = 'mian'
    bc_file_name = 'myproject'

    tu_dict = {}  # tu缓存
    file_cache = {}         #文件代码缓存
    tu = create_tu(file_path, tu_dict)
    global_type_dict = {}
    global_macro_dict = {}
    global_var_dict = {}

    # 分析文件中的枚举类型及其使用情况
    tu_type_dict, tu_macro_dict, tu_var_dict, tu_item_dict = parse_file(root_dir, tu, file_cache, global_type_dict,
                                                                        global_macro_dict, global_var_dict)

    code = read_file_content(file_path, file_cache)
    # 打印全局项目字典
    print("\nTu Items Tree:")
    print_tree(tu_item_dict, tu_macro_dict, tu_type_dict, tu_var_dict)



