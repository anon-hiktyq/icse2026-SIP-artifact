import http.client
import json
import os
import os.path as path
prompt = """
"你是一个c语言专家，帮我从.c代码和.h代码中提取出规范的知识模型。
JSON 格式概述了从软件 IP 代码中提取知识模型的结构，重点是功能描述、API 详情、接口、状态和参数。注意，功能描述使用中文，api描述使用符号表示
输出的json文件格式为{"functionDescription": "", "api": { "apiDescription": "", "interfaces": { "inputInterfaces": [ { "name": "", "type": "", "dimensionality": "", "meaning": "" }, { "name": "", "type": "", "dimensionality": "", "meaning": "" }, { "name": "", "type": "", "dimensionality": "", "meaning": "" }, { "name": "", "type": "", "dimensionality": "", "meaning": "" } ], "outputInterfaces": [ { "name": "", "type": "", "dimensionality": "", "meaning": "" }, { "name": "", "type": "", "dimensionality": "", "meaning": "" } ], "inoutInterfaces": [] }, "states": [ { "name": "", "type": "", "dimensionality": "", "meaning": "" } ], "parameters": [ { "name": "", "type": "", "dimensionality": "", "meaning": "" } ] }, }.c文件表示代码，.h文件表示接口。根据示例，帮我把下面的.c文件和.h文件的功能描述和接口信息提取处理。你要提取的.c文件为："""
# 配置部分
FILE_DIR = "IP2"  # 存放.c/.h文件的目录
API_ENDPOINT = ""
HEADERS = {'Content-Type': 'application/json','Authorization': 'Bearer sk-XEYvxfFYukYAKb4LA346529f85A34662891a8aC9075c82B3'};


def process_files(file_pairs):
    """处理文件对并保存结果"""
    conn = http.client.HTTPSConnection("")
    print(123)
    for c_path, h_path in file_pairs:
        try:
            # 读取文件内容
            with open(c_path, 'r', encoding='utf-8') as f:
                c_content = f.read()
            with open(h_path, 'r', encoding='utf-8') as f:
                h_content = f.read()

            # 构造prompt（保持原有模板不变）
            prompt_template = prompt + c_content + "你要提取的.h文件为" + h_content + "返回功能描述和接口信息的json，不要返回其它内容"

            payload = json.dumps({
                "model": "gpt-4o-2024-08-06",
                "messages": [{"role": "user", "content": prompt_template}],
                "max_tokens": 1688,
                "temperature": 0.5,
                "stream": False
            })
            # print(c_content)
            # print(h_content)

            # 发送请求
            conn.request("POST", API_ENDPOINT, payload, HEADERS)
            print("开始发送请求")
            res = conn.getresponse()
            print("取得返回结果")

            if res.status != 200:
                raw_data = res.read().decode("utf-8")
                data = json.loads(raw_data)
                print(data)
                print(f"API请求失败[{path.basename(c_path)}]: HTTP {res.status}")
                continue

            raw_data = res.read().decode("utf-8")
            data = json.loads(raw_data)
            print(data)
            # 提取关键内容
            try:
                content_str = data['choices'][0]['message']['content']
                print("识别结果为："+content_str)
                # result_data = json.loads(content_str)  # 二次解析JSON内容
            except (KeyError, IndexError) as e:
                print(f"响应结构异常[{path.basename(c_path)}]: {str(e)}")
                continue
            except json.JSONDecodeError as e:
                print(f"JSON解析失败[{path.basename(c_path)}]: {str(e)}")
                print(f"原始响应内容：\n{content_str[:200]}...")  # 打印前200字符辅助调试
                continue

            # 创建输出目录
            model_name = data.get("model", "unknown_model").replace("/", "_")
            output_dir = path.join("output-without2", model_name)
            os.makedirs(output_dir, exist_ok=True)

            # 保存结果
            base_name = path.splitext(path.basename(c_path))[0]
            output_path = path.join(output_dir, f"{base_name}.json")

            with open(output_path, 'w', encoding='utf-8') as f:
                json.dump(content_str, f,
                          indent=2,
                          ensure_ascii=False,  # 保留中文
                          sort_keys=True)  # 保持key顺序

            print(f"成功处理: {path.basename(c_path)} -> {output_path}")

        except Exception as e:
            print(f"处理异常[{path.basename(c_path)}]: {str(e)}")

    conn.close()


def find_file_pairs():
    """查找匹配的.c/.h文件对"""
    files = [f for f in os.listdir(FILE_DIR) if path.isfile(path.join(FILE_DIR, f))]
    pairs = []

    for f in files:
        if f.endswith(".c"):
            h_file = f[:-2] + ".h"
            if h_file in files:
                pairs.append(
                    (path.join(FILE_DIR, f),
                     path.join(FILE_DIR, h_file))
                )
    return pairs


if __name__ == "__main__":
    file_pairs = find_file_pairs()
    print(f"Found {len(file_pairs)} file pairs")
    process_files(file_pairs)



# print(prompt)
# conn.request("POST", "", payload, headers)
# res = conn.getresponse()
# data = res.read()
# # {"choices":[{"finish_reason":"stop","index":0,"logprobs":null,
# # "message":{"content":"晚上好！有什么我可以帮助你的吗？","refusal":null,"role":"assistant"}}],"created":1740965221,
# # "id":"chatcmpl-B6os9OqWWLvLtlURGMlrU9ev3Qt4x","model":"gpt-4o-2024-08-06","object":"chat.completion",
# # "system_fingerprint":"fp_b705f0c291","usage":{"completion_tokens":10,"completion_tokens_details":{"accepted_prediction_tokens":0,"audio_tokens":0,"reasoning_tokens":0,"rejected_prediction_tokens":0}
# # ,"prompt_tokens":9,"prompt_tokens_details":{"audio_tokens":0,"cached_tokens":0},"total_tokens":19}}
# print(data.decode("utf-8"))