#if !defined(__ISNEG_H__)
#define __ISNEG_H__

#include "common.h"




void isnegFun(void *p);

typedef struct __isneg
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	/* 输出端口 */
	int*			ret;
	/* 输入输出端口 */
	const char**			s;
	/* 状态变量 */
	/* 参数变量 */
} isneg;

#endif // __ISNEG_H__