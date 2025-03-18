#if !defined(__ISNEG_H__)
#define __ISNEG_H__

#include "common.h"





typedef struct __isneg
{
/* 接口函数 */
	void (*fun)( struct __isneg *);
/* 输入端口 */
	/* 输出端口 */
	int*			ret;
	/* 输入输出端口 */
	const char**			s;
	/* 状态变量 */
	/* 参数变量 */
} isneg;

void isnegFun(isneg *pIp);
#endif // __ISNEG_H__