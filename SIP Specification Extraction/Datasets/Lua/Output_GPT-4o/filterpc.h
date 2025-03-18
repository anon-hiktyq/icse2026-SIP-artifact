#if !defined(__FILTERPC_H__)
#define __FILTERPC_H__

#include "common.h"


typedef struct __filterpc
{
/* 接口函数 */
	void (*fun)( struct __filterpc *);
/* 输入端口 */
	int			pc;
	int			jmptarget;
	/* 输出端口 */
	int*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} filterpc;

void filterpcFun(filterpc *pIp);
#endif // __FILTERPC_H__