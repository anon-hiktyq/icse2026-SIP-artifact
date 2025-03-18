import subprocess
import argparse

class SyntaxChecker:
    def __init__(self):
        self.syntax_msg = ""  # 用于存储所有输出内容

    def parse_args(self):
        """设置命令行参数解析器"""
        parser = argparse.ArgumentParser(description="Run Frama-C WP on a C file.")
        parser.add_argument('file_name', help="Path to the C file to analyze")
        return parser.parse_args()

    def run(self, file_name=None):
        """运行 Frama-C WP 命令并处理输出"""
        if file_name is None:
            # 如果没有传入 file_name，从命令行参数获取
            args = self.parse_args()
            file_path = args.file_name
        else:
            # 如果传入了 file_name，直接使用
            file_path = file_name

        # 生成 WP 验证命令
        wp_command = [
            "frama-c",
            "-wp",
            "-wp-print",
            "-wp-timeout",
            "10",
            file_path
        ]

        try:
            # 使用 subprocess.run 运行命令，并捕获输出
            result = subprocess.run(wp_command, capture_output=True, text=True, check=True)
            self.syntax_msg = "syntax Correct"
        except subprocess.CalledProcessError as e:
            # 如果命令执行失败，捕获错误信息
            self.syntax_msg = "syntax Error\n" + e.stdout  # 将错误信息存入 syntax_msg

        print(self.syntax_msg)


if __name__ == "__main__":
    checker = SyntaxChecker()
    checker.run()
 