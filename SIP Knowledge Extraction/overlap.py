#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Time : 2025/3/15 15:28
# @Author : Haojie Feng

import os
import os.path as path
import json

# 配置部分
JSON_DIR = "reverse-output2-without/gpt-4o-2024-08-06"  # 存放json文件的目录
SOURCE_DIR = "IP2"  # 存放.c和.h文件的目录
OUTPUT_DIR = "reverse-overlap-output2-without"  # 存放输出结果的目录

def read_file(file_path):
    """读取文件内容"""
    with open(file_path, 'r', encoding='utf-8') as f:
        return f.read()

def process_raw_string(raw_string):
    """处理并解析原始字符串"""
    # 去掉Markdown标记
    json_string = raw_string.strip('```json').strip('```').strip()

    try:
        # 使用json.loads解析字符串
        json_data = json.loads(json_string)
        return json_data
    except json.JSONDecodeError as e:
        print(f"JSON解析失败: {str(e)}")
        return None

def calculate_coverage(json_content, source_content):
    """计算JSON内容在源文件中的覆盖率"""
    json_lines = json_content.splitlines()
    source_lines = source_content.splitlines()

    matched_lines = sum(1 for line in json_lines if line in source_lines)
    coverage = (matched_lines / len(json_lines)) * 100 if json_lines else 0
    return matched_lines, len(json_lines), coverage

def process_files():
    """处理文件并计算覆盖率"""
    json_files = {f[:-5]: f for f in os.listdir(JSON_DIR) if f.endswith('.json')}
    source_files = {f[:-2]: f for f in os.listdir(SOURCE_DIR) if f.endswith('.c') or f.endswith('.h')}

    matched_files = set(json_files.keys()) & set(source_files.keys())
    print(f"找到 {len(matched_files)} 个匹配的文件名")

    os.makedirs(OUTPUT_DIR, exist_ok=True)

    high_coverage_files = []
    total_matched_lines = 0
    total_json_lines = 0

    for file_name in matched_files:
        try:
            # 读取JSON文件内容
            with open(path.join(JSON_DIR, json_files[file_name]), 'r', encoding='utf-8') as f:
                raw_json_data = f.read()
            json_data = process_raw_string(raw_json_data)
            json_data = process_raw_string(json_data)
            if not json_data:
                continue

            # 拼接JSON中的c_file和h_file内容
            json_content = json_data.get('c_file', '') + '\n' + json_data.get('h_file', '')

            # 读取源文件内容
            source_content_c = read_file(path.join(SOURCE_DIR, file_name + '.c'))
            source_content_h = read_file(path.join(SOURCE_DIR, file_name + '.h'))

            # 拼接源文件内容
            source_content = source_content_c + '\n' + source_content_h

            # 计算覆盖率
            matched_lines, json_lines, coverage = calculate_coverage(json_content, source_content)
            total_matched_lines += matched_lines
            total_json_lines += json_lines

            if coverage >= 80:
                high_coverage_files.append((file_name, coverage))

            output = {
                "file_name": file_name,
                "coverage": coverage
            }

            output_path = path.join(OUTPUT_DIR, f"{file_name}_coverage.json")
            with open(output_path, 'w', encoding='utf-8') as f:
                json.dump(output, f, indent=2, ensure_ascii=False)

            print(f"处理完成：{file_name} -> {output_path}")

        except Exception as e:
            print(f"处理异常[{file_name}]: {str(e)}")

    # 输出覆盖率在80%以上的文件名及其比例
    if high_coverage_files:
        print("\n覆盖率在80%以上的文件及其比例：")
        for file, coverage in high_coverage_files:
            print(f"{file}: {coverage:.2f}%")
        print(f"\n总计：{len(high_coverage_files)} 个文件覆盖率在80%以上。")

    # 计算并输出总覆盖率
    total_coverage = (total_matched_lines / total_json_lines) * 100 if total_json_lines else 0
    print(f"\n总的代码覆盖率：{total_coverage:.2f}%")

if __name__ == "__main__":
    process_files()
