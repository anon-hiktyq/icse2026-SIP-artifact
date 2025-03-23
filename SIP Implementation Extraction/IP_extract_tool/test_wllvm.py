import os
import subprocess
from pathlib import Path
import sys
import shutil
import warnings
from collections import defaultdict
import json
from utils import find_headers_path

os.environ['LLVM_COMPILER'] = 'clang'
# venv_bin = os.path.join(sys.prefix, 'bin')
# os.environ['PATH'] = "$VIRTUAL_ENV/bin:$PATH" + os.environ['PATH']
# os.environ['PATH'] = f"{venv_bin}:{os.environ['PATH']}"

wllvm_path = "/home/dimpling/anaconda3/bin/wllvm"


def find_c_files(directory):
    """递归查找指定目录下的所有 .c 文件"""
    c_files = []
    for path in Path(directory).rglob('*.c'):
        c_files.append(str(path))
    return c_files


def find_h_files(directory):
    """递归查找指定目录下的所有 .h 文件"""
    h_files = []
    for path in Path(directory).rglob('*.h'):
        h_files.append(str(path))
    return h_files


def compile_with_wllvm(root_dir, headers = None):
    """使用 wllvm 编译 C 文件"""
    c_files = find_c_files(root_dir)


    # 构建编译命令
    cmd = [wllvm_path]
    cmd.extend(c_files)
    if headers:
        for header in headers:
            cmd.append(f'-I{header}')
    cmd.extend(['-g', '-I', '.', '-o', 'myproject'])
    print(f"编译命令: {' '.join(cmd)}")
    # if headers:
    #     # 将头文件路径转换为 -include 参数并添加到 args 中

    # 运行编译命令
    result = subprocess.run(cmd, capture_output=True, text=True)

    if result.returncode != 0:
        print("编译失败:")
        print(result.stderr)
        return None

    print("编译成功!")

def find_file_path(root_dir):

    # 1. 查找所有子目录
    subdirs = [root_dir]
    for dirpath, dirnames, _ in os.walk(root_dir):
        for dirname in dirnames:
            full_path = os.path.join(dirpath, dirname)

            subdirs.append(full_path)
    return subdirs

if __name__ == "__main__":
    target_fun_name = 'CO_LEDs'
    root_dir = '../Input/test12/Inventory_Management_System'  # 根目录（可以根据需要修改）
    source_file = '../Input/test12/Inventory_Management_System'  # 指定的 .c 文件
    subdirs = find_file_path(root_dir)
    print(f"返回的文件路径列表为:{subdirs}")
    compile_with_wllvm(source_file, subdirs)
