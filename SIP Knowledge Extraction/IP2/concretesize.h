#if !defined(__CONCRETESIZE_H__)
#define __CONCRETESIZE_H__

#include "common.h"




void concretesizeFun(void *p);

typedef struct __concretesize
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	unsigned int			size;
	/* 输出端口 */
	size_t*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} concretesize;

#endif // __CONCRETESIZE_H__