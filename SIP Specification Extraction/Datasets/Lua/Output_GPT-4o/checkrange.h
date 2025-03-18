#if !defined(__CHECKRANGE_H__)
#define __CHECKRANGE_H__

#include "common.h"




typedef struct __checkrange
{
/* 接口函数 */
	void (*fun)( struct __checkrange *);
/* 输入端口 */
	unsigned int			k;
	unsigned int			limit;
	/* 输出端口 */
	unsigned int*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} checkrange;

void checkrangeFun(checkrange *pIp);
#endif // __CHECKRANGE_H__