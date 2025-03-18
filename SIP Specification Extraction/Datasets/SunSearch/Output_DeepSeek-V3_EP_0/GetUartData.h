#if !defined(__GETUARTDATA_H__)
#define __GETUARTDATA_H__

#include "common.h"


typedef struct __GetUartData
{
/* 接口函数 */
	void (*fun)( struct __GetUartData *);
/* 输入端口 */
	const unint32			len;
	const unint32			addr;
	/* 输出端口 */
	unint32			bSucc;
	unint32*			ret;
	/* 输入输出端口 */
	unint08*			data;
	/* 状态变量 */
	/* 参数变量 */
} GetUartData;
void GetUartDataFun(GetUartData *p);
#endif // __GETUARTDATA_H__