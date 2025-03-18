import argparse
import subprocess
from syntaxChecker import SyntaxChecker
import re

class OutputVerifier:
    def __init__(self):
        self.file_name = None
        self.syntax_error = ''
        self.syntax_bool = None
        self.loop_error_list = []
        self.assert_error_list = []
        self.post_error_list = []
        self.loop_result = []
        self.assert_result =[]
        self.post_result =[]
       

    def print_errors(self, error_list):
        for error in error_list:
            print(error[0])  # 打印错误描述
            print(error[1])  # 打印错误文件位置
            print(error[2])  # 打印错误行内容
            print()
    
    def log_errors(self):
        # 创建一个字符串来存储日志内容
        log_content = ""

        # 添加文件名
        log_content += f"File Name: {self.file_name}\n\n"

        # 添加 syntax_error
        log_content += "Syntax Error:\n"
        log_content += f"{self.syntax_error}\n\n"

        # 添加 Loop Invariant Errors
        log_content += "Loop Invariant Errors:\n"
        if self.loop_error_list:
            for error in self.loop_error_list:
                log_content += f"- {error}\n"
        else:
            log_content += "No Loop Invariant Errors.\n"
        log_content += "\n"

        # 添加 Loop Invariant Results
        log_content += "Loop Invariant Results:\n"
        if self.loop_result:
            for result in self.loop_result:
                log_content += f"- {result}\n"
        else:
            log_content += "No Loop Invariant Results.\n"
        log_content += "\n"

        # 添加 Assertion Errors
        log_content += "Assertion Errors:\n"
        if self.assert_error_list:
            for error in self.assert_error_list:
                log_content += f"- {error}\n"
        else:
            log_content += "No Assertion Errors.\n"
        log_content += "\n"

        # 添加 Assertion Results
        log_content += "Assertion Results:\n"
        if self.assert_result:
            for result in self.assert_result:
                log_content += f"- {result}\n"
        else:
            log_content += "No Assertion Results.\n"
        log_content += "\n"

        # 添加 Postcond Errors
        log_content += "Postcond Errors:\n"
        if self.post_error_list:
            for error in self.post_error_list:
                log_content += f"- {error}\n"
        else:
            log_content += "No Postcond Errors.\n"
        log_content += "\n"

        # 添加 Postcond Results
        log_content += "Postcond Results:\n"
        if self.post_result:
            for result in self.post_result:
                log_content += f"- {result}\n"
        else:
            log_content += "No Postcond Results.\n"
        log_content += "\n"

        # 添加分隔线
        log_content += '------------------------------------------------\n'

        # 返回日志内容
        return log_content

    def log_accury(self):
        
        def calculate_accuracy(bool_array):
            if not bool_array:  # 如果数组为空，返回 0
                return 0.0
            return (sum(bool_array) / len(bool_array)) * 100  # 转换为百分数
        
        loop_accuracy = calculate_accuracy(self.loop_result)
        assert_accuracy = calculate_accuracy(self.assert_result)
        post_accuracy = calculate_accuracy(self.post_result)
        

        # 计算总的正确率
        combined_results = self.loop_result + self.assert_result + self.post_result
        total_accuracy = calculate_accuracy(combined_results)
        
        accuracy_log = f'''
File Name: {self.file_name}
synatax_accuracy: {self.syntax_bool}
loop_accuracy:  {loop_accuracy:.2f}% ({sum(self.loop_result)}/{len(self.loop_result)})
assert_accuracy:  {assert_accuracy:.2f}% ({sum(self.assert_result)}/{len(self.assert_result)})
post_accuracy:  {post_accuracy:.2f}%  ({sum(self.post_result)}/{len(self.post_result)})
total_accuracy:  {total_accuracy:.2f}% ({sum(combined_results)}/{len(combined_results)})
'''
        # print(accuracy_log)
        return accuracy_log

    def extract_semantic_error(self,error_message):
        # 使用正则表达式提取文件名和行号
        pattern = r'file\s+([\w\/\.\-]+),\s+line\s+(\d+)'
        match = re.search(pattern, error_message)
        
        if match:
            file_path = match.group(1)
            line_number = int(match.group(2))  # 转换为整数

            try:
                with open(file_path, 'r') as file:
                    # 读取文件的所有行
                    lines = file.readlines()
                    # 检查行号是否在文件范围内
                    if 1 <= line_number <= len(lines):
                        error_line = lines[line_number - 1].strip()  # 提取错误行内容
                    else:
                        error_line = None  # 行号超出范围
                    
            except FileNotFoundError:
                print(f"Error: File '{file_path}' not found.")
                return None, None

            # 构造错误位置信息和错误行内容信息
            error_location_msg = f"Error found in file: {file_path} at line: {line_number}"
            error_content_msg = f"Error line content: {error_line}" if error_line else "Error line content: Line number out of range or file could not be read."

            return error_location_msg, error_content_msg
        
        else:
            return None, None
    

    def check_pairs(self, filter_invs):
        results = []
        # 按相邻相同的元素分组
        for i in range(0, len(filter_invs), 2):
            if "Valid" in str(filter_invs[i]) and "Valid" in str(filter_invs[i+1]):
                results.append(True)
            else:
                results.append(False)
        return results

    def check_target(self, filter_contents):
        results = []
        for content in filter_contents:
            if 'Valid' in content:
                results.append(True)
            else:
                results.append(False)
        return results

    def filter_goal_assertion(self, contents):
        return [line for line in contents if line.strip().startswith("Goal Assertion ") or line.strip().startswith("Goal Assigns ")]

    def filter_invariant(self, contents):
        return [line for line in contents if line.strip().startswith("Goal Establishment of Invariant") or line.strip().startswith("Goal Preservation of Invariant")]

    def filter_post_condition(self, contents):
        return [line for line in contents if line.strip().startswith("Goal Post-condition ")]
    

    
    def parse_args(self):
        parser = argparse.ArgumentParser(description="Run Frama-C WP on a C file.")
        parser.add_argument('file_name', help="Path to the C file to analyze")
        return parser.parse_args()
    
    def run(self,file_name=None):

        if file_name != None:
            file_path = f"Output/{file_name}"
            self.file_name = file_name
        else :
            args = self.parse_args()
            file_path = f"Output/{args.file_name}"
            self.file_name = args.file_name

        # syntax_msg = subprocess.run(['python3', 'syntaxChecker.py', file_path], capture_output=True, text=True).stdout
        # print(syntax_msg)

        checker = SyntaxChecker()
        checker.run(file_path)
        syntax_msg = checker.syntax_msg

        if syntax_msg !='syntax Correct':
            self.syntax_error = syntax_msg
            self.syntax_bool = False
        else:
            self.syntax_bool = True
            frama_c_command = "frama-c"
            wp_command = [frama_c_command, "-wp", "-wp-print", "-wp-timeout", "3", "-wp-prover", "z3", "-wp-model", "Typed+Caveat", file_path]
            result = subprocess.run(wp_command, capture_output=True, text=True, check=True)
            spliter = '------------------------------------------------------------'
            content = result.stdout
            contents = content.split(spliter)
            
    
            filter_invs = self.filter_invariant(contents)
            self.loop_result = self.check_pairs(filter_invs)

            for item in filter_invs:
                if 'Valid' not in item:
                    loop_error_msg = item
                    error_location_msg, error_content_msg = self.extract_semantic_error(loop_error_msg)
                    self.loop_error_list.append((loop_error_msg.strip(), error_location_msg, error_content_msg))

            print('Loop Invariant:')
            print(self.loop_result)
            print()
            # self.print_errors(self.loop_error_list)

            filter_contents = self.filter_goal_assertion(contents)
            self.assert_result = self.check_target(filter_contents)

            for item in filter_contents:
                if 'Valid' not in item:
                    assert_error_msg = item
                    error_location_msg, error_content_msg = self.extract_semantic_error(assert_error_msg)
                    self.assert_error_list.append((assert_error_msg.strip(), error_location_msg, error_content_msg))

            print('Assertion:')
            print(self.assert_result)
            print()
            # self.print_errors(self.assert_error_list)

            filter_postconds = self.filter_post_condition(contents)
            self.post_result = self.check_target(filter_postconds)
            
            for item in filter_postconds:
                if 'Valid' not in item:
                    post_error_msg = item
                    error_location_msg, error_content_msg = self.extract_semantic_error(post_error_msg)
                    self.post_error_list.append((post_error_msg.strip(), error_location_msg, error_content_msg))
            
            print('Post Condition:')
            print(self.post_result)
            print()
            # self.print_errors(self.post_error_list)


    

if __name__ == "__main__":
    verifier = OutputVerifier()
    verifier.run()