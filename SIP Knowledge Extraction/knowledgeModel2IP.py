#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Time : 2025/3/15 15:28
# @Author : Haojie Feng
import http.client
import json
import os
import os.path as path

prompt = """
"你是一个c语言专家，能够帮我从一个json格式的知识模型当中提取出.c和.h文件。
示例如下：输入的json文件：
输入的json文件内容{"functionDescription": "IP内部记录陀螺使用状态，若陀螺使用状态发生变化，则按照序号从小到大的顺序选择5个陀螺，计算它们的安装矩阵。", "api": { "apiDescription": "void CalculateGyroRsFun(void p);", "interfaces": { "inputInterfaces": [ { "name": "JoinTotal", "type": "unint08", "dimensionality": "个", "meaning": "参加定姿的陀螺个数" }, { "name": "gyroStatus0", "type": "unint16", "dimensionality": "", "meaning": "本周期新的陀螺状态（从B0~B8依次表示序号为1至序号为9的陀螺可用标志；1为可用，0为不可用）" }, { "name": "wa", "type": "float32", "dimensionality": "", "meaning": "陀螺角速度模拟量数组首地址指针" }, { "name": "SignFlag", "type": "unint08*", "dimensionality": "", "meaning": "参加定姿的陀螺序号数组首地址指针" } ], "outputInterfaces": [ { "name": "flgGryoCalc", "type": "unint08", "dimensionality": "", "meaning": "陀螺安装矩阵更新标志，TRUE32为本周期更新；FALSE32为本周期未更新" }, { "name": "Rtemp", "type": "float32[3][5]", "dimensionality": "", "meaning": "陀螺安装矩阵矩阵计算结果" } ], "inoutInterfaces": [] }, "states": [ { "name": "VG", "type": "float32[9][3]", "dimensionality": "", "meaning": "全部陀螺在卫星本体坐标系下的安装矩阵" } ], "parameters": [ { "name": "gyroStatus1", "type": "unint16", "dimensionality": "", "meaning": "上周期的陀螺状态（从B0~B8依次表示序号为1至序号为9的陀螺可用标志；1为可用，0为不可用）" } ] }, }.c文件表示代码，.h文件表示接口。根据示例，帮我把下面的.c文件和.h文件的功能描述和接口信息提取处理。
输出的.c文件是
"#if !defined(__CALCULATEGYRORS_H__)
#define __CALCULATEGYRORS_H__

#include "../../IP.h"

void CalculateGyroRsFun(void *p);

/* 计算陀螺相关矩阵 */
typedef struct __CalculateGyroRs
{
   /* 接口函数 */
   Fun fun;
   /* 输入端口 */
   unint08 JoinTotal;   /* 参加定姿的陀螺个数 */
   unint16 gyroStatus0; /* 陀螺状态新 */
   unint08 *SignFlag;   /* 参加定姿的陀螺序号数组指针 */
   /* 输出端口 */
   unint08 flgGryoCalc; /* 陀螺计算标志 */
   float32 Rtemp[3][5]; /* 矩阵计算结果 */
   /* 输入输出端口 */
   /* 状态变量 */
   unint16 gyroStatus1; /* 陀螺状态旧 */
   /* 参数变量 */
   float32 VG[9][3];
} CalculateGyroRs;

#endif // __CALCULATEGYRORS_H__
"
} 
输出的.h文件：
"
#include "CalculateGyroRs.h"

void CalculateGyroRsFun(void *p)
{
    CalculateGyroRs *pIp = (CalculateGyroRs*)p;
	unint08 i ;									
 	unint08 j ;									
	unint08 k ;									
 	float32 Rgtrans[3][5] ;									
 	float32 Rs[3][3] ;									
	float32 RsInv[3][3] ;									
 	float32 Rgtemp[5][3] ;									

 	pIp->JoinTotal = MIN(pIp->JoinTotal, 5) ;												

	if (pIp->gyroStatus0 != pIp->gyroStatus1)		/* 有陀螺切换 */
	{		                                                
		pIp->flgGryoCalc = TRUE ;								/* 置陀螺计算标志 */

		for ( j=0 ; j<pIp->JoinTotal ; j++ )			/* 参加定姿的陀螺个数 */
		{                                                               				
			k = pIp->SignFlag[j] ;						/* 按从小到大排列依次选5个，不足5个选余下的 */								

			for ( i=0 ;  i<3 ; i++ )                        
			{                                               
				Rgtemp[j][i] = pIp->VG[k][i] ;					/* n*3的安装阵R */						
			}                                               
		}                                                   

		for ( i = pIp->JoinTotal ; i<5 ; i++ )			/* 不用的（5-JoinTotal）维，清零 */
		{
			for ( j=0 ; j<3 ; j++ )
			{
				Rgtemp[i][j] = 0.0f;										
			}
		}

		if (pIp->JoinTotal >= 3)						/* 若大于三个陀螺工作可以计算角速度 */
		{                                                                       

			MatrixTran(&Rgtrans[0][0], &Rgtemp[0][0], 5, 3) ;					/* Rg->Rgtrans    		*/								
			MatrixMulti(&Rs[0][0], &Rgtrans[0][0], &Rgtemp[0][0], 3, 5, 3) ;	/* R*RT->RS       		*/								
			MatrixInv33F(&RsInv[0][0], &Rs[0][0]) ;								/* INV(RS)->RsInv 		*/		
			MatrixMulti(&pIp->Rtemp[0][0], &RsInv[0][0], &Rgtrans[0][0], 3, 3, 5) ;	/* RsInv*Rgtrans->Rtemp */									
		}		
		pIp->gyroStatus1 = pIp->gyroStatus0 ;									
	}
    return;}"""
# 配置部分
JSON_DIR = "output-without2/gpt-4o-2024-08-06"  # 存放json的目录
API_ENDPOINT = ""
HEADERS = {'Content-Type': 'application/json',
           'Authorization': ''};


def process_json_files():
    """处理JSON文件并发送请求"""
    conn = http.client.HTTPSConnection("")

    json_files = [f for f in os.listdir(JSON_DIR) if f.endswith('.json')]
    print(f"找到 {len(json_files)} 个JSON文件")

    for json_file in json_files:
        try:
            # 读取JSON文件内容
            with open(path.join(JSON_DIR, json_file), 'r', encoding='utf-8') as f:
                json_content = f.read()

            # 构造提示词
            prompt_template = prompt + "你要处理的json内容是"+json_content+"返回.c文件和.h的json格式，.c文件存放在c_file中，.h文件存放在h_file中。不要返回其它内容"

            payload = json.dumps({
                "model": "gpt-4o-2024-08-06",
                "messages": [{"role": "user", "content": prompt_template}],
                "max_tokens": 1688,
                "temperature": 0.5,
                "stream": False
            })

            # 发送请求
            conn.request("POST", API_ENDPOINT, payload, HEADERS)
            print(f"正在发送请求：{json_file}")
            res = conn.getresponse()

            if res.status != 200:
                raw_data = res.read().decode("utf-8")
                data = json.loads(raw_data)
                print(data)
                print(f"API请求失败[{json_file}]: HTTP {res.status}")
                continue

            raw_data = res.read().decode("utf-8")
            data = json.loads(raw_data)
            print(data)

            # 提取并保存结果
            try:
                content_str = data['choices'][0]['message']['content']
                print(f"{json_file}的响应结果：{content_str}")

                # 创建输出目录
                model_name = data.get("model", "unknown_model").replace("/", "_")
                output_dir = path.join("reverse-output2-without", model_name)
                os.makedirs(output_dir, exist_ok=True)

                # 保存结果
                output_path = path.join(output_dir, f"{path.splitext(json_file)[0]}.json")
                with open(output_path, 'w', encoding='utf-8') as f:
                    json.dump(content_str, f, indent=2, ensure_ascii=False, sort_keys=True)

                print(f"成功处理：{json_file} -> {output_path}")

            except (KeyError, IndexError) as e:
                print(f"响应结构异常[{json_file}]: {str(e)}")
                continue
            except json.JSONDecodeError as e:
                print(f"JSON解析失败[{json_file}]: {str(e)}")
                print(f"原始响应内容：\n{content_str[:200]}...")  # 打印前200字符辅助调试
                continue

        except Exception as e:
            print(f"处理异常[{json_file}]: {str(e)}")

    conn.close()

if __name__ == "__main__":
    process_json_files()

# print(prompt)
# conn.request("POST", "/v1/chat/completions", payload, headers)
# res = conn.getresponse()
# data = res.read()
# # {"choices":[{"finish_reason":"stop","index":0,"logprobs":null,
# # "message":{"content":"晚上好！有什么我可以帮助你的吗？","refusal":null,"role":"assistant"}}],"created":1740965221,
# # "id":"chatcmpl-B6os9OqWWLvLtlURGMlrU9ev3Qt4x","model":"gpt-4o-2024-08-06","object":"chat.completion",
# # "system_fingerprint":"fp_b705f0c291","usage":{"completion_tokens":10,"completion_tokens_details":{"accepted_prediction_tokens":0,"audio_tokens":0,"reasoning_tokens":0,"rejected_prediction_tokens":0}
# # ,"prompt_tokens":9,"prompt_tokens_details":{"audio_tokens":0,"cached_tokens":0},"total_tokens":19}}
# print(data.decode("utf-8"))
