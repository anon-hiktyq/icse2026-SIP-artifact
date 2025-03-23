from main import *
import os
import argparse

os.environ['LLVM_COMPILER'] = 'clang'


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("secondary_range", help="C 文件的路径")
    parser.add_argument("function_name", help="要分析的目标函数名称")
    # 解析命令行参数
    args = parser.parse_args()
    file_path = args.file_path
    function_name = args.function_name
    root_dir = '/'.join(file_path.split('/')[:-1])

    print(f'根目录为: {root_dir}')


    function_info_dict = {}
    function_info_dict = function_info_init(file_path, function_name, function_info_dict)
    print(function_info_dict)

    fun_var_dict, modify_code, modify_struct = (
        fun_to_IP(root_dir, file_path, function_name))

    # 修改目标函数的源代码
    function_info_dict[function_name].code = modify_code

    code_list, headers_dict, refined_dict, global_dict = (
        print_content_update(function_info_dict[function_name], function_info_dict))
    print(code_list)

    # 将函数结构体包含的全局变量删掉
    # print(global_dict)
    # for key in global_dict:
    # #     if key in IP_var_dict:
    #         del global_dict[key]

    write_dicts_to_h(function_name, headers_dict, refined_dict, global_dict, modify_struct)
    write_dicts_to_c(function_name, code_list)

if __name__ == "__main__":
    main()
