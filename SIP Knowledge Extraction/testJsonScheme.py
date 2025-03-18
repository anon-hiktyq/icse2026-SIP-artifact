import os
import json
from jsonschema import validate, ValidationError

# 定义 JSON Schema
schema = {
    "type": "object",
    "properties": {
        "functionDescription": {"type": "string"},
        "api": {
            "type": "object",
            "properties": {
                "apiDescription": {"type": "string"},
                "interfaces": {
                    "type": "object",
                    "properties": {
                        "inputInterfaces": {
                            "type": "array",
                            "items": {
                                "type": "object",
                                "properties": {
                                    "name": {"type": "string"},
                                    "type": {"type": "string"},
                                    "dimensionality": {"type": "string"},
                                    "meaning": {"type": "string"}
                                },
                                "required": ["name", "type", "meaning"]
                            }
                        },
                        "outputInterfaces": {
                            "type": "array",
                            "items": {
                                "type": "object",
                                "properties": {
                                    "name": {"type": "string"},
                                    "type": {"type": "string"},
                                    "dimensionality": {"type": "string"},
                                    "meaning": {"type": "string"}
                                },
                                "required": ["name", "type", "meaning"]
                            }
                        },
                        "inoutInterfaces": {
                            "type": "array",
                            "items": {
                                "type": "object",
                                "properties": {
                                    "name": {"type": "string"},
                                    "type": {"type": "string"},
                                    "dimensionality": {"type": "string"},
                                    "meaning": {"type": "string"}
                                },
                                "required": ["name", "type", "meaning"]
                            }
                        }
                    },
                    "required": ["inputInterfaces", "outputInterfaces", "inoutInterfaces"]
                },
                "states": {
                    "type": "array",
                    "items": {
                        "type": "object",
                        "properties": {
                            "name": {"type": "string"},
                            "type": {"type": "string"},
                            "meaning": {"type": "string"}
                        },
                        "required": ["name", "type", "meaning"]
                    }
                },
                "parameters": {
                    "type": "array",
                    "items": {
                        "type": "object",
                        "properties": {
                            "name": {"type": "string"},
                            "type": {"type": "string"},
                            "defaultValue": {"type": "string"},
                            "meaning": {"type": "string"}
                        },
                        "required": ["name", "type", "meaning"]
                    }
                }
            },
            "required": ["apiDescription", "interfaces", "states", "parameters"]
        }
    },
    "required": ["functionDescription", "api"]
}

# 验证 JSON 数据的函数
def validate_json(data, schema):
    try:
        validate(instance=data, schema=schema)
        return True
    except ValidationError as e:
        return False

# 遍历目录并验证 JSON 文件
def validate_json_files_in_directory(directory):
    valid_count = 0
    total_count = 0

    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith('.json'):
                total_count += 1
                file_path = os.path.join(root, file)
                with open(file_path, 'r', encoding='utf-8') as f:
                    try:
                        data = json.load(f)
                        if validate_json(data, schema):
                            valid_count += 1
                            print(f"{file_path}: Valid")
                        else:
                            print(f"{file_path}: Invalid")
                    except json.JSONDecodeError:
                        print(f"{file_path}: Invalid JSON format")

    print(f"Validation completed: {valid_count}/{total_count} files are valid.")

# 指定要遍历的目录
directory_to_check = "output-without2/gpt-4o-2024-08-06"
validate_json_files_in_directory(directory_to_check)
