#ifndef __FG_3_3_3SA_H__
#define __FG_3_3_3SA_H__

#include "std_basal.h"
#include "std_bitop.h"
#include "std_common.h"

typedef struct TAG_FG_3_3_3SA_RAW
{
	float64 gf;           /* 角度增量 */
	float64 wt0;				/* 陀螺头原始角速度 */
	unint32 cntFrame;		   /* 帧计数 */
	
	unint32 bComSuc;      /* 通信成功标志 */
	
	siint32 cntLenRd;		 /* 连续读取长度错误计数 */		
	siint32 cntHead;		  /* 连续帧头错误计数 */
	siint32 cntLen;		   /* 连续长度错误计数(指的是协议中的长度信息) */
	siint32 cntCheck;		 /* 连续校验错误计数 */
	siint32 cntUpdata;		/* 连续数据更新错误计数 */
	
	siint32 totalLenRd;	   /* 累计读取长度错误计数 */  
	siint32 totalHead;		/* 累计帧头错误计数 */	
	siint32 totalLen;		 /* 累计长度错误计数 */	
	siint32 totalCheck;	   /* 累计校验错误计数 */	
	siint32 totalUpdata;	  /* 累计数据更新错误计数 */

	unint16 glwd1;/* 光路温度 */
	unint16 glwd2;/* 光路温度 */
	unint16 dlwd;/* 电路温度 */
	unint08 status;/* 状态字 */
} SFg333saRaw;

extern unint32 SendFg333saCmd(unint08 *pSendBuf);
extern unint32 Fg333saCheck(const unint08 *pbuff, unint32 rdLen, unint32 *frm, unint32 *pFgRaw);
extern void Fg333saUnPack(unint32 *pFgRaw, const unint08 *pRecvbuf,float64 dtime);
/* 功能描述：8位整型数组，加法累加和计算，输出8位累加和 函数体在静态链接库中（基础公共运算库函数） */
extern unint08 CheckSumAdd08(const unint08 *buffer, unint32 length);
#endif

