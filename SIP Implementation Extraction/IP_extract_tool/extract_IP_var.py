import os
import subprocess
from pathlib import Path
import sys
import shutil
import warnings
from collections import defaultdict
import json
from utils import read_json_file

os.environ['LLVM_COMPILER'] = 'clang'


# venv_bin = os.path.join(sys.prefix, 'bin')
# os.environ['PATH'] = "$VIRTUAL_ENV/bin:$PATH"
# os.environ['PATH'] = f"{venv_bin}:{os.environ['PATH']}"


def compile_with_wllvm(root_dir, headers=None):
    """使用 wllvm 编译 C 文件"""
    c_files = []
    for ext in ('*.c', '*.C'):
        c_files.extend(str(f) for f in Path(root_dir).rglob(ext))

    if not c_files:
        print("没有找到 .c 或 .C 文件。")
        return None

    cmd = ['wllvm', *c_files, '-g', '-I', '.']
    # if headers:
    #     cmd.extend(f'-I {header}' for header in headers)
    cmd.extend(['-o', 'myproject'])

    result = subprocess.run(cmd, capture_output=True, text=True)
    if result.returncode != 0:
        print(f"编译失败:\n{result.stderr}")
        return None

    print("编译成功!")


def extract_bitcode(bc_file_name):
    """从可执行文件中提取比特码"""

    cmd = ['extract-bc', f'{bc_file_name}']
    print(f"提取比特码命令: {' '.join(cmd)}")

    result = subprocess.run(cmd, capture_output=True, text=True)

    if result.returncode != 0:
        print("提取比特码失败:")
        print(result.stderr)
        return None

    print("比特码提取成功!")


def move_files_to_root_dir(root_dir, bc_file_name):
    """将生成的文件移动到目标目录"""
    os.makedirs(root_dir, exist_ok=True)

    for item in os.listdir():
        if item.endswith(('.o', '.bc')):
            try:
                shutil.move(item, os.path.join(root_dir, item))
                print(f"已移动: {item}")
            except Exception as e:
                print(f"移动 {item} 失败: {e}")


def run_sip(root_dir, bc_file_name):
    """运行 sip 工具并解析其输出"""

    target_path = root_dir + f'/{bc_file_name}.bc'

    try:
        # 调用 sip 工具并捕获输出
        result = subprocess.run(['../build/src/sip', target_path, '-extapi=../dependency/svf_install/lib/extapi.bc'],
                                capture_output=True, text=True, check=True)
        sip_output = result.stdout

        # 初始化标志和解析输出
        capturing = False
        parsed_output = []

        # 解析 sip 输出
        for line in sip_output.splitlines():
            if not capturing and '##### Function:' in line:
                capturing = True  # 找到第一个 '##### Function:' 后开始捕捉有效信息
            if capturing:
                parsed_output.append(line)  # 捕捉有效信息
        print(parsed_output)
        return parsed_output

    except subprocess.CalledProcessError as e:
        print(f"运行 sip 工具失败: {e.stderr}")
    except Exception as e:
        print(f"发生错误: {e}")


def create_IP_params_dict(data_list: list) -> dict:
    """
    生成IP参数字典，确保记录所有遇到的函数。
    输入的数据列表应该包含函数及其变量信息的描述行。
    """
    current_var_type = None
    # print

    # 初始化字典结构
    function_dict = defaultdict(lambda: {k: {} for k in ['input', 'output', 'stateVar', 'argVar']})
    current_function = None

    # 第一步：收集所有函数名
    for line in data_list:
        if '##### Function:' in line:
            function_name = line.replace('##### Function:', '').replace('#####', '').strip()
            print(function_name)
            if 'llvm' not in function_name.lower():
                # 为每个非llvm函数创建空字典结构
                function_dict[function_name] = {
                    'input': {},
                    'output': {},
                    'stateVar': {},
                    'argVar': {}
                }

    # 遍历数据列表中的每一行
    for line in data_list:
        # 检查是否是新的函数定义行
        if '##### Function:' in line:
            # 提取函数名
            current_function = line.replace('##### Function:', '').replace('#####', '').strip()
            # 如果函数名包含'llvm'，则跳过该函数
            if 'llvm' in current_function.lower():
                current_function = None
            continue

        # 如果当前没有在处理任何函数，则跳过
        if not current_function:
            continue

        # 检查是否是变量类型定义行
        if any(key in line for key in ['input:', 'output:', 'stateVar:', 'argVar:']):
            current_var_type = line.split(':')[0].strip()
            continue

        # 如果不是变量类型定义行，则尝试解析变量名和类型
        if 'varName:' in line and current_var_type:
            parts = line.split('varType:')
            if len(parts) != 2:
                warnings.warn(f"无法解析变量信息：{line}")
                continue

            var_name = parts[0].replace("varName:","").strip()
            var_type = parts[1].strip()

            # 将变量信息添加到对应的函数字典中
            function_dict[current_function][current_var_type][var_name] = var_type

    return dict(function_dict)


def create_fun_var_dict(function_name, function_dict):
    """
    从给定的字典中提取指定函数的参数，并将参数以 {'name': 'type'} 的形式返回。该字典没有'Input'等关键字

    :param function_dict: 包含所有函数及其参数的字典
    :param function_name: 要提取参数的函数名称
    :return: 一个包含指定函数参数的字典，格式为 {'name': 'type'}
    """
    # 检查函数名称是否存在
    if function_name not in function_dict:
        raise KeyError(f"Function '{function_name}' not found in the dictionary.")

    # 获取指定函数的参数
    function_info = function_dict[function_name]

    # 初始化结果字典
    fun_var_dict = {}

    # 定义需要处理的类别
    categories = ['input', 'output', 'stateVar', 'argVar']

    # 添加 input 字段中的参数
    for category in categories:
        if category in function_info and isinstance(function_info['input'], dict):
            fun_var_dict.update(function_info[category])
    return fun_var_dict


def refine_IP_var_dict(IP_var_dict):
    # 需要检查的字典列表
    vars_to_check = ["stateVar", "argVar"]

    # 获取所有需要删除的键
    keys_to_remove = set()
    for var in vars_to_check:
        keys_to_remove.update(IP_var_dict[var].keys())

    # 从 input 和 output 中删除这些键
    for key in keys_to_remove:
        IP_var_dict["input"].pop(key, None)
        IP_var_dict["output"].pop(key, None)
    return IP_var_dict


def extract_IP_var(root_dir, bc_file_name, headers_path=None, target_fun_name=None):
    """提取IP变量信息的主函数"""
    if not Path(root_dir).is_dir():
        print(f"无效目录: {root_dir}")
        return

    json_path = f'{root_dir}/IP_var_data.json'

    #如果没有建立json
    if not os.path.isfile(json_path):
        venv_bin = os.path.join(sys.prefix, 'bin')
        os.environ['PATH'] = f"{venv_bin}:$VIRTUAL_ENV/bin:{os.environ['PATH']}"

        #如果根目录没有以.bc结尾的文件，则编译
        if not any(file.endswith('.bc') for file in os.listdir(root_dir)):
            compile_with_wllvm(root_dir, headers_path)  #运行wllvm

        #如果没有{bc_file_name}.bc文件，则提取比特码
        if not os.path.isfile(f'{bc_file_name}.bc'):
            extract_bitcode(bc_file_name)  #运行extract_bc
        move_files_to_root_dir(root_dir, bc_file_name)
        parsed_output = run_sip(root_dir, bc_file_name)  #运行sip
        ip_params_dict = create_IP_params_dict(parsed_output)
        with open(json_path, 'w') as f:
            json.dump(ip_params_dict, f, indent=4)
            print(f'成功生成json文件: {json_path}')

    if target_fun_name:
        ip_params_dict = read_json_file(json_path)
        fun_var_dict = create_fun_var_dict(target_fun_name, ip_params_dict)
        IP_var_dict = refine_IP_var_dict(ip_params_dict[target_fun_name])
        return fun_var_dict, IP_var_dict


def find_file_path(root_dir):
    # 1. 查找所有子目录
    subdirs = [root_dir]
    for dirpath, dirnames, _ in os.walk(root_dir):
        for dirname in dirnames:
            full_path = os.path.join(dirpath, dirname)

            subdirs.append(full_path)
    return subdirs


if __name__ == "__main__":
    file_path = '../Input/lua/linit.c'
    root_dir = '../Input/lua'
    function_name = 'luaL_openselectedlibs'
    bc_file_name = 'lua'
    subdirs = find_file_path(root_dir)
    print(f"返回的文件路径列表为:{subdirs}")
    fun_var_dict, IP_fun_vars = extract_IP_var(root_dir, bc_file_name, subdirs, function_name)
    print(fun_var_dict)
    print(IP_fun_vars)