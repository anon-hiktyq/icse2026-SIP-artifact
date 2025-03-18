import clang.cindex
from main_class import CalleeInfo, FunMacroExprInfo
from utils import (read_file_content, create_tu,
                   find_function_cursor, is_from_standard_library, record_content_range, find_c_file_path, record_range_content)
from tree_sitter_app import callee_info_update



def record_macro_set(fun_item_dict):
    """
    记录所有宏展开的函数调用
    """
    # 获取函数调用节点的起始位置
    macro_set = set()
    
    for item in fun_item_dict:
        if item['kind'] == 'macro':
            macro_set.add(item.split('@')[0])

    return macro_set


def callees_info_init(root_dir, tu_dict, caller_cursor, file_cache, tu_item_dict, function_info_dict, unparsed_fun_set):
    """
    找到所有非标准库的被调用函数
    """
    callee_info_list = []
    caller_start_line = caller_cursor.location.line

    # 当遇到函数调用时,不再遍历它的子节点
    def visit(cursor, is_function_call = False):

        if is_function_call:
            return
        
        # 如果当前节点是一个函数调用表达式
        if cursor.kind == clang.cindex.CursorKind.CALL_EXPR:

            callee_range = record_content_range(cursor, caller_start_line)

            # if not is_macro_expr(callee_range, macro_expr_info_list):
            # 获取被调用函数声明的游标
            del_cursor = cursor.referenced

            # 如果callee是非标准库函数
            if del_cursor is not None and not is_from_standard_library(del_cursor):

                is_function_call = True
                # 记录callee的名称
                name = del_cursor.spelling
                # print(f'\ncallee name:\n{name}')

                #如果已经在function_info_dict中,直接提取路径
                if name in function_info_dict.keys():
                    file_path = function_info_dict[name].path
                # 记录callee声明代码的路径
                else:
                    file_path = find_c_file_path(root_dir, name, tu_dict)

                #如果没有找到,可能是编译器内置指令等,我们跳过
                if file_path is None:
                    return

                # print(f'\n\nfile path:\n{file_path}\n')

                function_code = record_range_content(read_file_content(file_path, file_cache), record_content_range(caller_cursor))
                print(function_code)
                new_callee_info = CalleeInfo(name, file_path, callee_range, cursor, del_cursor)

                # 更新callee的var_mapping和sub_function_info_list
                callee_info_update(function_code, tu_dict, tu_item_dict, new_callee_info, unparsed_fun_set, root_dir)

                callee_info_list.append(new_callee_info)

        # 递归遍历子节点
        for child in cursor.get_children():
            visit(child, is_function_call)

    # 从调用者函数的游标开始遍历
    visit(caller_cursor)

    return callee_info_list


def print_callee_structure(callee_info_list, indent=0):
    """
    递归打印callee_info_list的结构
    
    :param callee_info_list: CalleeInfo对象列表
    :param indent: 当前缩进级别
    """
    indent_str = "    " * indent
    for callee_info in callee_info_list:
        print(f"{indent_str}Function: {callee_info.name}")
        print(f"{indent_str}├── File: {callee_info.file_path}")
        print(f"{indent_str}├── Range: {callee_info.content_range}")
        print(f"{indent_str}└── Arguments:")
        
        for param, arg in callee_info.var_mapping.items():
            if isinstance(arg, CalleeInfo):
                # 如果参数是嵌套的函数调用
                print(f"{indent_str}    ├── {param} = (Function Call):")
                print_callee_structure([arg], indent + 2)
            else:
                # 如果参数是普通值
                print(f"{indent_str}    ├── {param} = {arg}")
        print()


if __name__ == "__main__":
    clang.cindex.Config.set_library_path('/usr/lib/llvm-18/lib')
    # 初始化 libclang 索引
    index = clang.cindex.Index.create()
    # file_path = '../Input/SAMCode_V1.01/g4eapp.c'
    # root_dir = '../Input/SAMCode_V1.01'
    # target_function_name = 'LimitCtrlRateInput'

    file_path = '../Input/test16/test.c'
    root_dir = '../Input/test16'
    function_name = 'main'
    bc_file_name = 'myproject'

    tu_dict = {}
    # 解析 C 文件
    tu = create_tu(file_path,tu_dict)

    caller_cursor = find_function_cursor(tu, function_name)
    print(f"caller's name is : {caller_cursor.spelling}")

    # callee_info_list = parse_callee(root_dir, file_path, tu, caller_cursor, tu_dict)
    #
    # print("\nCallee Structure:")
    # print("================")
    # print_callee_structure(callee_info_list)

