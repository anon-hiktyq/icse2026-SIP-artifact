from fun_to_IP import app
import os
import argparse
import tree_sitter_c as tspython
from tree_sitter import Language, Parser
C_LANGUAGE = Language(tspython.language())
parser = Parser(C_LANGUAGE)

os.environ['LLVM_COMPILER'] = 'clang'


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("file_path", help="c. file_path")
    parser.add_argument("root_dir", help="root_dir")
    parser.add_argument("function_name", help="target function_name")
    parser.add_argument("bc_file_name", help=".bc file_name")
    # 解析命令行参数
    args = parser.parse_args()

    file_path = args.file_path
    root_dir = args.root_dir
    function_name = args.function_name
    bc_file_name = args.bc_file_name

    app(file_path, root_dir, function_name, bc_file_name)

if __name__ == "__main__":
    main()
