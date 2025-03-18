#if !defined(__BINSEARCH_H__)
#define __BINSEARCH_H__

#include "common.h"
#include arraykeyisempty.h

#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif


void binsearchFun(void *p);

typedef struct __binsearch
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	Table*			array;
	unsigned int			j;
	/* 输出端口 */
	unsigned int*			ret;
	/* 输入输出端口 */
	unsigned int			i;
	/* 状态变量 */
	/* 参数变量 */
} binsearch;

#endif // __BINSEARCH_H__