#if !defined(__SENDUARTDATA_H__)
#define __SENDUARTDATA_H__

#include "common.h"


typedef struct __SendUartData
{
/* 接口函数 */
	void (*fun)( struct __SendUartData *);
/* 输入端口 */
	const unint32			addr;
	const unint08*			data;
	const unint32			len;
	/* 输出端口 */
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} SendUartData;
void SendUartDataFun(SendUartData *p);
#endif // __SENDUARTDATA_H__