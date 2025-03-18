import os
import subprocess
import re

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

    return headers

def find_subdirs(root_dir):
    # 配置参数


    # 1. 查找所有子目录
    """
    递归查找根目录下的所有子目录。
    """
    subdirs = [root_dir]
    for dirpath, dirnames, _ in os.walk(root_dir):
        for dirname in dirnames:
            full_path = os.path.join(dirpath, dirname)

            subdirs.append(full_path)

    return subdirs


from pathlib import Path


def find_c_files(directory):
    """递归查找指定目录下的所有 .c 文件"""
    c_files = []
    for path in Path(directory).rglob('*.c'):
        c_files.append(str(path))
    return c_files


# def compile_with_wllvm(root_dir, headers = None):
#     """使用 wllvm 编译 C 文件"""
#     c_files = []
#     for ext in ('*.c', '*.C'):
#         c_files.extend(Path(root_dir).rglob(ext))
#     c_files = [str(f) for f in c_files]
#     if not c_files:
#         print("没有找到 .c 或 .C 文件。")
#         return None
#
#     # 构建编译命令
#     cmd = ['wllvm']
#     cmd.extend(c_files)
#     if headers:
#         for header in headers:
#             cmd.append(f'-I{header}')
#     cmd.extend(['-g', '-I', '.', '-o', 'myproject'])
#     print(f"编译命令: {' '.join(cmd)}")
#     # if headers:
#     #     # 将头文件路径转换为 -include 参数并添加到 args 中
#
#     # 运行编译命令
#     result = subprocess.run(cmd, capture_output=True, text=True)
#
#     if result.returncode != 0:
#         print("编译失败:")
#         print(result.stderr)
#         return None
#
#     print("编译成功!")



def compile_with_wllvm(c_files, output_executable, include_dirs=None, extra_flags=None):
    """
    使用 wllvm 编译 C 文件为可执行文件，并生成 LLVM IR。

    :param c_files: .c 文件列表
    :param output_executable: 输出的可执行文件名
    :param include_dirs: 包含头文件的目录列表
    :param extra_flags: 额外的编译选项
    """
    if not c_files:
        print("没有找到任何 .c 文件！")
        return

    # 构建命令
    command = ['wllvm']

    # 添加输出选项
    command.extend(['-o', output_executable])

    # 添加包含目录
    if include_dirs:
        for include_dir in include_dirs:
            command.extend(['-I', include_dir])

    # 添加额外的编译选项
    if extra_flags:
        command.extend(extra_flags)

    # 添加所有 .c 文件
    command.extend(c_files)

    # 打印编译命令
    print("编译命令:", ' '.join(command))

    # 执行编译
    try:
        result = subprocess.run(command, check=True)
        if result.returncode == 0:
            print(f"编译成功，生成的可执行文件: {output_executable}")

            # 提取 LLVM IR
            extract_command = ['extract-bc', output_executable]
            ir_file = f"{output_executable}.bc"
            print("提取 LLVM IR 命令:", ' '.join(extract_command))
            subprocess.run(extract_command, check=True)
            print(f"LLVM IR 文件已生成: {ir_file}")
    except subprocess.CalledProcessError as e:
        print(f"编译失败: {e}")


if __name__ == "__main__":
    # 项目根目录
    project_directory = "../Input/test15/CANopenNode"

    # 输出的可执行文件名
    output_executable = "my_program"

    subdirs = find_subdirs(project_directory)

    # 包含头文件的目录（如果有多个，可以用列表指定）
    include_dirs = subdirs  # 如果没有，可以设置为 None

    # 额外的编译选项（例如优化选项、调试信息等）
    extra_flags = ["-O2", "-g"]  # 如果没有，可以设置为 None

    # 查找所有 .c 文件
    c_files = find_c_files(project_directory)

    # 使用 wllvm 编译项目
    compile_with_wllvm(c_files, output_executable, include_dirs=include_dirs, extra_flags=extra_flags)

# if __name__ == "__main__":
#     root_dir = '../Input/test15/CANopenNode'  # 根目录（可以根据需要修改）
#     source_file = '../Input/test15/CANopenNode/301/CO_Emergency.c'  # 指定的 .c 文件
#     find_headers_path(root_dir, source_file)