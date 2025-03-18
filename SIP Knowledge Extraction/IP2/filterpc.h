#if !defined(__FILTERPC_H__)
#define __FILTERPC_H__

#include "common.h"




void filterpcFun(void *p);

typedef struct __filterpc
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	int			pc;
	int			jmptarget;
	/* 输出端口 */
	int*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} filterpc;

#endif // __FILTERPC_H__