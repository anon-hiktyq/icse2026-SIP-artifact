import os
import openai
import re
import time
import shutil
from outputVerify import OutputVerifier

class SpecGenerator:

    def __init__(self):

        self.m = 1
        self.n = 3
        self.llm ='deepseek-v3'
        self.prompt = 'ultra' 
    
        self.client = None
        self.messages = None


    def __reit__(self ,m,n,llm=None, prompt =None):

        self.m = m
        self.n = n

        if llm !=None:
            self.llm = llm

        if prompt !=None:
            self.prompt = prompt


    def clear_folder(self,folder_path='Result'):
        # 检查文件夹是否存在
        if os.path.exists(folder_path):
            # 遍历文件夹中的所有文件和子文件夹
            for filename in os.listdir(folder_path):
                file_path = os.path.join(folder_path, filename)
                try:
                    # 如果是文件，则删除
                    if os.path.isfile(file_path) or os.path.islink(file_path):
                        os.unlink(file_path)
                    # 如果是文件夹，则递归删除
                    elif os.path.isdir(file_path):
                        shutil.rmtree(file_path)
                except Exception as e:
                    print(f'Failed to delete {file_path}. Reason: {e}')
        else:
            print(f"The folder {folder_path} does not exist.")

    def copy_and_overwrite(self, input_dir='Input', output_dir='Output', extensions=['.c']):
        # 确保输出目录存在
        if not os.path.exists(output_dir):
            os.makedirs(output_dir)

        # 遍历输入目录中的所有文件
        for filename in os.listdir(input_dir):
            input_path = os.path.join(input_dir, filename)
            output_path = os.path.join(output_dir, filename)

            # 如果是文件且扩展名匹配
            if os.path.isfile(input_path) and (extensions is None or any(filename.endswith(ext) for ext in extensions)):
                shutil.copy2(input_path, output_path)

    def get_user_prompt(self, c_code):
        """从文件中读取 prompt 模板并替换占位符"""
        with open(f"prompt/{self.prompt}/base_prompt.txt", "r", encoding="utf-8") as file:
            prompt_template = file.read()
        user_prompt = prompt_template.format(c_code=c_code)
        return user_prompt

    def generate_acsl_spec(self, c_code):
        """调用大模型生成ACSL规约"""
        prompt = self.get_user_prompt(c_code)

        try:
            """调用 OpenAI API 获取 ACSL 注释"""
            # 将内容添加到消息中
            self.messages.append({"role": "user", "content": prompt})

            # 获取助手的响应
            response = self.client.chat.completions.create(
                model=self.llm,
                messages=self.messages,
                temperature=0.3
            )

            def extract_last_c_code(text):
                # 匹配 C 代码块（Markdown 代码块 或 以 #include 开头的代码）
                code_blocks = re.findall(r'```c(.*?)```', text, re.DOTALL)  # Markdown 代码块

                return code_blocks[-1] if code_blocks else text  # 返回最后一个 C 代码块

            # 处理响应
            assistant_response = response.choices[0].message.content
            assistant_response = re.sub(r'>\s*Reasoning\s*[\s\S]*?(?=\n\n|$)', '', assistant_response, flags=re.IGNORECASE)
            assistant_response = re.sub(r'<think>.*?</think>', '', assistant_response, flags=re.DOTALL)
            assistant_response = extract_last_c_code(assistant_response)

            return assistant_response

        except Exception as e:
            print(f"API调用失败: {e}")
            return None



    def modify_spec(self, error_message, c_code):
        """调用大模型生成ACSL规约"""
        prompt = self.get_syntax_feedback_prompt(error_message, c_code)

        try:
            """调用 OpenAI API 获取 ACSL 注释"""
            # 将内容添加到消息中
            self.messages.append({"role": "user", "content": prompt})

            # 获取助手的响应
            response = self.client.chat.completions.create(
                model=self.llm,
                messages=self.messages,
                temperature=0.3
            )

            def extract_last_c_code(text):
                # 匹配 C 代码块（Markdown 代码块 或 以 #include 开头的代码）
                code_blocks = re.findall(r'```c(.*?)```', text, re.DOTALL)  # Markdown 代码块

                return code_blocks[-1] if code_blocks else text  # 返回最后一个 C 代码块

            # 处理响应
            assistant_response = response.choices[0].message.content
            assistant_response = re.sub(r'>\s*Reasoning\s*[\s\S]*?(?=\n\n|$)', '', assistant_response, flags=re.IGNORECASE)
            assistant_response = re.sub(r'<think>.*?</think>', '', assistant_response, flags=re.DOTALL)
            assistant_response = extract_last_c_code(assistant_response)

            return assistant_response

        except Exception as e:
            print(f"API调用失败: {e}")
            return None

    def regen_spec(self, error_list, c_code):
        """调用大模型生成ACSL规约"""

        def format_errors(error_list):
            if not error_list:
                return "No errors found."

            error_str = []

            for index, (desc, location, content) in enumerate(error_list, start=1):
                error_str.append(f"Error {index}: {desc}")
                error_str.append(f"Location: {location}")
                error_str.append(f"Code: {content}")
                error_str.append("-" * 50)

            return "\n".join(error_str)

        error_str = format_errors(error_list)

        prompt = self.get_semantic_feedback_prompt(error_str, c_code)

        try:
            """调用 OpenAI API 获取 ACSL 注释"""
            # 将内容添加到消息中
            self.messages.append({"role": "user", "content": prompt})

            # 获取助手的响应
            response = self.client.chat.completions.create(
                model=self.llm,
                messages=self.messages,
                temperature=0.3
            )

            def extract_last_c_code(text):
                # 匹配 C 代码块（Markdown 代码块 或 以 #include 开头的代码）
                code_blocks = re.findall(r'```c(.*?)```', text, re.DOTALL)  # Markdown 代码块

                return code_blocks[-1] if code_blocks else text  # 返回最后一个 C 代码块

            # 处理响应
            assistant_response = response.choices[0].message.content
            assistant_response = re.sub(r'>\s*Reasoning\s*[\s\S]*?(?=\n\n|$)', '', assistant_response, flags=re.IGNORECASE)
            assistant_response = re.sub(r'<think>.*?</think>', '', assistant_response, flags=re.DOTALL)
            assistant_response = extract_last_c_code(assistant_response)

            return assistant_response

        except Exception as e:
            print(f"API调用失败: {e}")
            return None

    def get_semantic_feedback_prompt(self, error_str, c_code):
        # 从文件中读取 prompt 模板
        with open(f"prompt/{self.prompt}/semantic_error.txt", "r", encoding="utf-8") as file:
            prompt_template = file.read()

        # 替换模板中的 {code} 占位符
        user_prompt = prompt_template.format(error_str=error_str, c_code=c_code)

        return user_prompt

    def get_syntax_feedback_prompt(self, error_message, c_code):
        # 从文件中读取 prompt 模板
        with open(f"prompt/{self.prompt}/syntax_error.txt", "r", encoding="utf-8") as file:
            prompt_template = file.read()

        # 替换模板中的 {code} 占位符
        user_prompt = prompt_template.format(error_message=error_message, c_code=c_code)

        return user_prompt

    def are_true(self, loop_result, assert_result, post_result):
        if not loop_result and not assert_result and not post_result:
            return False

        # 使用 all() 函数判断每个列表中的所有元素是否为 True
        loop_all_true = all(loop_result)
        assert_all_true = all(assert_result)
        post_all_true = all(post_result)

        # 返回三个列表是否都为 True
        return loop_all_true and assert_all_true and post_all_true
    
    def get_score(self, loop_result, assert_result, post_result):
        if not loop_result and not assert_result and not post_result:
            return -1
    
        def calculate_accuracy(bool_array):
            if not bool_array:  # 如果数组为空，返回 0
                return 0.0
            return (sum(bool_array) / len(bool_array)) * 100  # 转换为百分数

        # 计算总的正确率
        combined_results = loop_result + assert_result + post_result
        total_accuracy = calculate_accuracy(combined_results)

        return total_accuracy

    def process_single_file(self, input_file, output_dir="Output"):
        """对单个文件生成ACSL注释"""



        if not os.path.exists(output_dir):
            os.makedirs(output_dir)

        # 提取文件名（不带路径和后缀）
        filename = os.path.basename(input_file)

        output_file = os.path.join(output_dir, f"{filename}")

        # 读取C文件内容
        with open(input_file, "r", encoding="utf-8") as f:
            c_code = f.read()

        best_code = None
        best_score = -1
        

        print(f"正在处理文件: {filename}")

        llm_time = 0

        self.client = openai.OpenAI(
            base_url="https://yunwu.ai/v1",
            api_key="api-key"
        )
        self.messages = [{"role": "system", "content": "You are a helpful assistant."}]


        flag = False
        print(self.m)
        for _ in range(self.m):

            acsl_spec = self.generate_acsl_spec(c_code)
            llm_time = llm_time + 1

            # 保存结果
            if acsl_spec:
                flag = True
                with open(output_file, "w", encoding="utf-8") as f:
                    f.write(acsl_spec)

                print(f"已生成ACSL文件: {output_file}")

                verifier = OutputVerifier()

                verifier.run(filename)  # 传入完整路径
                is_True = self.are_true(verifier.loop_result, verifier.assert_result, verifier.post_result)
                score =self.get_score(verifier.loop_result, verifier.assert_result, verifier.post_result)

                if score > best_score:
                    best_score = score
                    best_code = acsl_spec
                if is_True:
                    print('规约正确')
                    return llm_time
                
      
                for _ in range(self.n):
                    # 验证生成的ACSL文件
                    if verifier.syntax_bool == False:

                        # 如果存在语法错误，调用 LLM 修复语法错误
                        acsl_spec = self.modify_spec(verifier.syntax_error, acsl_spec)
                        llm_time = llm_time + 1  # 记录 LLM 调用次数

                        # 保存修复后的 ACSL 文件
                        with open(output_file, "w", encoding="utf-8") as f:
                            f.write(acsl_spec)
                            print(f"已修改ACSL语法错误: {output_file}")

                        # 重新验证修复后的文件
                        verifier.run(filename)
                        is_True = self.are_true(verifier.loop_result, verifier.assert_result, verifier.post_result)
                        score =self.get_score(verifier.loop_result, verifier.assert_result, verifier.post_result)

                        if score > best_score:
                            best_score = score
                            best_code = acsl_spec

                        if is_True:
                            print('规约正确')
                            return llm_time  # 如果规约正确，直接返回

                    else:

                        # if self.prompt =='ultra':
                        #     print('语法正确')
                        #     return llm_time  # 如果规约正确，直接返回

                        # 如果语法正确但逻辑错误，调用 LLM 修复逻辑错误
                        error_list = verifier.loop_error_list + verifier.assert_error_list + verifier.post_error_list
                        acsl_spec = self.regen_spec(error_list, acsl_spec)
                        llm_time = llm_time + 1  # 记录 LLM 调用次数
                    
                        # 保存修复后的 ACSL 文件
                        with open(output_file, "w", encoding="utf-8") as f:
                            f.write(acsl_spec)
                            print(f"已修改ACSL错误规约: {output_file}")

                        # 重新验证修复后的文件
                        verifier.run(filename)
                        is_True = self.are_true(verifier.loop_result, verifier.assert_result, verifier.post_result)

                        score =self.get_score(verifier.loop_result, verifier.assert_result, verifier.post_result)

                        if score > best_score:
                            best_score = score
                            best_code = acsl_spec

                        if is_True:
                            print('规约正确')
                            return llm_time  # 如果规约正确，直接返回
                        
                        
                        

        print(f"达到最大 LLM 调用次数 ({self.m} * {self.n})，未找到正确规约")
            

        if flag == False:
            print(f"生成失败: {filename}")

        if score > -1:
            with open(output_file, "w", encoding="utf-8") as f:
                                f.write(best_code)
                                print(f"已生成最佳规约: {output_file}")
        else:
             print(f"无法生成语法正确的规约")

        return llm_time

    def process_files(self, input_dir="Output", output_dir="Output"):
        """遍历input文件夹并生成ACSL文件"""
        if not os.path.exists(output_dir):
            os.makedirs(output_dir)

        loop_results = []
        assert_results = []
        post_results = []

        count = 0
        correct = 0
        total_generate_time = 0  # 总生成时间
        total_verify_time = 0  # 总验证时间
        total_llm_time = 0




        for filename in os.listdir(input_dir):
            if filename.endswith(".c"):
                
                count = count + 1

                input_path = os.path.join(input_dir, filename)

                
                 # 新增文件存在性检查
                if  os.path.exists(f'Result/result_{self.llm}_{self.m}{self.n}_{self.prompt}.txt'):
                
                    with open(f'Result/result_{self.llm}_{self.m}{self.n}_{self.prompt}.txt', "r", encoding="utf-8") as f:
                        msg = f.read()
                    

                    if f"File Name: {filename}" in msg:
                        continue


                generate_time_start = time.time()

                llm_time = self.process_single_file(input_path, output_dir)
            

                generate_time_end = time.time()
                generate_time = generate_time_end - generate_time_start

                total_generate_time += generate_time
                total_llm_time += llm_time

                # 记录验证开始时间
                verify_start_time = time.time()

                verifier = OutputVerifier()
                verifier.run(filename)
                with open(f'Result/error_{self.llm}_{self.m}{self.n}_{self.prompt}.txt', 'a') as f:
                      f.write(verifier.log_errors())

                # 记录验证结束时间
                verify_end_time = time.time()
                verify_time = verify_end_time - verify_start_time
                total_verify_time += verify_time  # 累加验证时间

                with open(f'Result/result_{self.llm}_{self.m}{self.n}_{self.prompt}.txt', 'a') as f:
                    f.write(verifier.log_accury())
                    f.write(f"llm_time: {llm_time}\n")
                    f.write(f"generate_time: {generate_time:.2f} s\n")
                    f.write(f"verify_time: {verify_time:.2f} s\n")
                    f.write("--------------------------------------------\n")

                if verifier.syntax_bool == True:
                    correct = correct + 1

                loop_results += verifier.loop_result
                assert_results += verifier.assert_result
                post_results += verifier.post_result

        combined_results = loop_results + assert_results + post_results

        def calculate_accuracy(bool_array):
            if not bool_array:  # 如果数组为空，返回 0
                return 0.0
            return (sum(bool_array) / len(bool_array)) * 100  # 转换为百分数

        loop_accuracy = calculate_accuracy(loop_results)
        assert_accuracy = calculate_accuracy(assert_results)
        post_accuracy = calculate_accuracy(post_results)
        total_accuracy = calculate_accuracy(combined_results)
        syntax_accuracy = (correct / count) * 100

        with open(f'Result/result_{self.llm}_{self.m}{self.n}_{self.prompt}.txt', 'a') as f:
            # 计算每个数组的正确率并写入文件
            f.write("----------------------------------------------")
            f.write(f"\nRESULT\n")
            f.write(f"syntax_accuracy:{syntax_accuracy:.2f}% ({correct}/{count}) \n" )
            f.write(f"loop_accuracy:  {loop_accuracy:.2f}%  ({sum(loop_results)}/{len(loop_results)}) \n" )
            f.write(f"assert_accuracy:  {assert_accuracy:.2f}% ({sum(assert_results)}/{len(assert_results)}) \n" )
            f.write(f"post_accuracy:  {post_accuracy:.2f}% ({sum(post_results)}/{len(post_results)}) \n" )
            f.write(f"total_accuracy:  {total_accuracy:.2f}% ({sum(combined_results)}/{len(combined_results)}) \n" )
            f.write(f"total_llm_time:  {total_llm_time}\n")
            f.write(f"total_generate_time: {total_generate_time:.2f} s\n")
            f.write(f"total_verify_time: {total_verify_time:.2f} s\n")
            f.write(f"average_llm_time:  {(total_llm_time / 50):.2f}\n")
            f.write(f"average_generate_time: {(total_generate_time / 50):.2f} s\n")
            f.write(f"average_verify_time: {(total_verify_time / 50):.2f} s\n")
            f.write("--------------------------------------------\n")


if __name__ == "__main__":
    
    generator = SpecGenerator()
    generator.process_files()








