from extract_all import parse_file
from parse_function import *
import clang.cindex
from extract_all import parse_file,create_tu
import os
from main_class import *
from extract_IP_var import extract_IP_var, find_file_path
from utils import find_c_file_path

os.environ['LLVM_COMPILER'] = 'clang'


# 辅助函数：检查一个范围是否在另一个范围内
def is_range_inside(inner_range, outer_range):
    """
    检查inner_range是否完全在outer_range内部

    :param inner_range: [start_line, start_col, end_line, end_col]
    :param outer_range: [start_line, start_col, end_line, end_col]
    :return: 如果inner_range在outer_range内，返回True；否则返回False
    """
    # 检查起始位置
    if inner_range[0] < outer_range[0] or (inner_range[0] == outer_range[0] and inner_range[1] < outer_range[1]):
        return False

    # 检查结束位置
    if inner_range[2] > outer_range[2] or (inner_range[2] == outer_range[2] and inner_range[3] > outer_range[3]):
        return False

    return True


# Add the new function to initialize global dictionaries
def global_dict_init(root_dir, file_path, function_name, function_info_dict, tu_dict, file_cache, global_type_dict,
                     global_macro_dict, global_var_dict, bc_file_name):
    """
    使用迭代方法初始化全局字典，避免递归处理大量数据
    
    :param root_dir: 项目根目录
    :param file_path: 文件路径
    :param function_name: 函数名称
    :param function_info_dict: 函数信息字典
    :param tu_dict: 翻译单元字典
    :param file_cache: 文件缓存
    :param global_type_dict: 全局类型字典
    :param global_macro_dict: 全局宏字典
    :param global_var_dict: 全局变量字典
    :param bc_file_name: BC文件名称
    """
    # 使用队列存储待处理的函数
    functions_to_process = [(file_path, function_name)]
    processed_functions = set()
    
    # 使用迭代方法处理所有函数
    while functions_to_process:
        current_file_path, current_function_name = functions_to_process.pop(0)
        
        # 如果函数已经处理过，跳过
        if current_function_name in processed_functions or current_function_name in function_info_dict:
            continue

        processed_functions.add(current_function_name)
        print(f'开始创建函数Info: {current_function_name},path:{current_file_path}')
        # 创建翻译单元
        tu = create_tu(current_file_path, tu_dict)
        
        # 获取该tu的信息
        tu_type_dict, tu_macro_dict, tu_var_dict, tu_item_dict = parse_file(root_dir, tu, file_cache, global_type_dict, global_macro_dict, global_var_dict)
        
        # 获取该函数的所有信息
        relevant_header_set, content_range, function_code, fun_item_dict, macro_expr_info_list, callee_info_list, function_cursor, func_type, ret_range_list, unparsed_fun_set \
            = parse_function(root_dir, current_file_path, current_function_name, tu, file_cache, tu_dict, tu_item_dict,
                             tu_type_dict,
                             function_info_dict)

        subdirs = find_file_path(root_dir)
        # 获取接口信息
        fun_var_dict, IP_var_dict = extract_IP_var(root_dir, bc_file_name, subdirs, current_function_name)
        
        # 处理 fun_var_dict 和 IP_var_dict
        if fun_var_dict and IP_var_dict:
            # 删除那些在 output 类别中但不在 input 类别中的变量
            if 'output' in IP_var_dict and 'input' in IP_var_dict:
                output_only_vars = set()
                for var_name in IP_var_dict['output']:
                    if var_name not in IP_var_dict['input']:
                        output_only_vars.add(var_name)
                
                # 从 fun_var_dict 中删除这些变量
                for var_name in output_only_vars:
                    if var_name in fun_var_dict:
                        print(f"从 fun_var_dict 中删除输出变量: {var_name}")
                        del fun_var_dict[var_name]
                
                # 从 IP_var_dict['output'] 中删除这些变量
                for var_name in output_only_vars:
                    if var_name in IP_var_dict['output']:
                        print(f"从 IP_var_dict['output'] 中删除变量: {var_name}")
                        del IP_var_dict['output'][var_name]

        # 更新全局字典
        global_type_dict.update(tu_type_dict)
        global_macro_dict.update(tu_macro_dict)
        global_var_dict.update(tu_var_dict)

        # 创建函数的function_info并加入字典
        function_info_dict[current_function_name] = FunctionInfo(
            path=current_file_path,
            code=function_code,
            fun_item_dict=fun_item_dict,
            macro_expr_info_list=macro_expr_info_list,
            callee_info_list=callee_info_list,
            fun_var_dict=fun_var_dict,
            IP_var_dict=IP_var_dict,
            function_cursor=function_cursor,
            func_type=func_type,
            ret_range_list=ret_range_list,
        )

        print(f'成功处理函数: {current_function_name}')

        # 将所有被调用的函数添加到待处理队列
        if callee_info_list:
            for callee_info in callee_info_list:
                if callee_info.name not in processed_functions and callee_info.name not in function_info_dict:
                    functions_to_process.append((callee_info.file_path, callee_info.name))
        if unparsed_fun_set:
            for unparsed_fun in unparsed_fun_set:
                if unparsed_fun not in processed_functions and unparsed_fun not in function_info_dict:
                    unparsed_fun_file_path = find_c_file_path(root_dir, unparsed_fun, tu_dict)
                    functions_to_process.append((unparsed_fun_file_path, unparsed_fun))

    print('全局字典初始化完成')
    print(f'已处理函数:')
    for func_name in function_info_dict:
        print(f'name: {func_name}; path: {function_info_dict[func_name].path}')



def remove_macro_expr_callee(callee_info_list, fun_macro_expr_info_list:list[FunMacroExprInfo]):
    for callee_info in callee_info_list:
        for fun_macro_expr_info in fun_macro_expr_info_list:
            if is_range_inside(callee_info.content_range, fun_macro_expr_info.content_range):
                print(f"删除了含参宏中的callee:{callee_info.name}")
                callee_info_list.remove(callee_info)

    #
    # # 删除所有在含参宏内的callee
    # filtered_callee_info_list = []
    # for callee_info in callee_info_list:
    #     is_in_macro = False
    #     for macro_expr in macro_expr_info_list:
    #         # 检查callee的范围是否在宏表达式的范围内
    #         if is_range_inside(callee_info.secondary_range, macro_expr.secondary_range):
    #             is_in_macro = True
    #             print(f"移除在宏 {macro_expr.name} 内的函数调用: {callee_info.name}")
    #             break
    #     if not is_in_macro:
    #         filtered_callee_info_list.append(callee_info)
    #
    # # 更新callee_info_list
    # callee_info_list = filtered_callee_info_list
    # print(f"过滤后的callee数量: {len(callee_info_list)}")

def global_dict_update(function_info_dict, global_type_dict, global_macro_dict, global_var_dict, item_count_dict):
    """
    使用迭代方法对global_type_dict, global_macro_dict, global_var_dict中item进行记数，
    确定哪些item需要通过条件编译避免重复编译，并为每个function_info创建集合callee_item_set
    
    :param function_info_dict: 函数信息字典
    :param global_type_dict: 全局类型字典
    :param global_macro_dict: 全局宏字典
    :param global_var_dict: 全局变量字典
    :param item_count_dict: 项目计数字典
    """
    print(f'开始处理全局字典')
    
    # 初始化item_count_dict
    for key in global_type_dict:
        item_count_dict[key] = 0
    for key in global_macro_dict:
        item_count_dict[key] = 0
    for key in global_var_dict:
        item_count_dict[key] = 0
    
    print(f'初始化item_count_dict完成')
    
    # 使用拓扑排序的思想处理函数依赖关系
    # 首先计算每个函数的入度（被依赖的次数）
    in_degree = {func_name: 0 for func_name in function_info_dict}
    for func_name, func_info in function_info_dict.items():
        for callee_info in func_info.callee_info_list:
            if callee_info.name in in_degree:
                in_degree[callee_info.name] += 1
    
    # 使用队列存储入度为0的函数（没有被其他函数依赖的函数）
    queue = [func_name for func_name, degree in in_degree.items() if degree == 0]
    
    # 处理所有函数
    while queue:
        current_func_name = queue.pop(0)
        current_func_info = function_info_dict[current_func_name]

        # 收集相关callee的信息
        callee_item_set = set()
        
        # 收集所有callee的item
        for callee_info in current_func_info.callee_info_list:
            if callee_info.name in function_info_dict:
                callee_func_info = function_info_dict[callee_info.name]
                
                # 添加callee的callee_item_set
                if callee_func_info.callee_item_set:
                    callee_item_set.update(callee_func_info.callee_item_set)
                
                # 添加callee的fun_item_dict
                if callee_func_info.fun_item_dict:
                    callee_item_set.update(callee_func_info.fun_item_dict.keys())
        
        # 将callee_item_set传给function_info
        current_func_info.callee_item_set = callee_item_set
        
        # 更新item_count_dict
        for item_name in item_count_dict:
            # 当该item未被其他函数依赖:
            if item_name in current_func_info.fun_item_dict and item_count_dict[item_name] == 0:
                item_count_dict[item_name] += 1
            # 当该item已经被其他函数依赖:
            elif item_name in current_func_info.fun_item_dict and item_count_dict[item_name] > 0:
                # 如果该item未被callee引用过,代表被其他不相关函数使用,count+1
                if item_name not in callee_item_set:
                    item_count_dict[item_name] += 1
        
        # 更新依赖当前函数的函数的入度
        for func_name, func_info in function_info_dict.items():
            for callee_info in func_info.callee_info_list:
                if callee_info.name == current_func_name:
                    in_degree[func_name] -= 1
                    if in_degree[func_name] == 0:
                        queue.append(func_name)
    
    print(f'全局字典处理完成')


def print_global_dicts(global_type_dict, global_macro_dict, global_var_dict, function_info_dict, item_count_dict):
    """
    Print the contents of the global dictionaries.

    :param global_type_dict: Dictionary containing global types.
    :param global_macro_dict: Dictionary containing global macros.
    :param global_var_dict: Dictionary containing global variables.
    :param function_info_dict: Dictionary containing function information.
    :param item_count_dict: Dictionary containing callee usage counts.
    """
    print("\n=== Global Type Dictionary ===")
    for key, value in global_type_dict.items():
        print(f"{key}: {value}")

    print("\n=== Global Macro Dictionary ===")
    for key, value in global_macro_dict.items():
        print(f"{key}: {value}")

    print("\n=== Global Variable Dictionary ===")
    for key, value in global_var_dict.items():
        print(f"{key}: {value}")

    print("\n=== Function Information Dictionary ===")
    for key, function_info in function_info_dict.items():
        print(f"{key}: {function_info}")

    print("\n=== Item Count Dictionary ===")
    for key, count in item_count_dict.items():
        print(f"{key}: {count}")


if __name__ == '__main__':

    # file_path = '../Input/test7/main.c'
    # file_path = '../Input/SAMCode_V1.01/g4eapp.c'
    # root_dir = '../Input/SAMCode_V1.01'
    # bc_file_name = 'myproject'
    # function_name = 'main'

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

    file_path = '../Input/lua/lstring.c'
    root_dir = '../Input/lua'
    function_name = 'luaS_newlstr'
    bc_file_name = 'lua'  # debug:当顶层出现函数调用,此时上下文为none,会将none传回


    global_type_dict = {}
    global_macro_dict = {}
    global_var_dict = {}
    tu_dict = {}
    file_cache = {}
    function_info_dict = {}
    item_count_dict = {} #记录item被并行使用次数

    #初始化全局字典
    global_dict_init(root_dir, file_path, function_name, function_info_dict, tu_dict, file_cache, global_type_dict,
                     global_macro_dict, global_var_dict, bc_file_name)

    print('更新全局字典')
    #更新全局字典
    global_dict_update(function_info_dict, global_type_dict,global_macro_dict, global_var_dict, item_count_dict)

    #删去代码实际为宏的callee
    for function_info in function_info_dict.values():
        remove_macro_expr_callee(function_info.callee_info_list, function_info.macro_expr_info_list)

    # Print the contents of the global dictionaries
    print_global_dicts(global_type_dict, global_macro_dict, global_var_dict, function_info_dict, item_count_dict)



