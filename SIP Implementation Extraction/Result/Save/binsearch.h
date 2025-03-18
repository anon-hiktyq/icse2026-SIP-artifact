#if !defined(__BINSEARCH_H__)
#define __BINSEARCH_H__

#include "common.h"
#include "arraykeyisempty.h"

#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif


void binsearchFun(void *p);

typedef struct __binsearch
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	Table*			array;
	unsigned int			j;
	/* Output Variables */
	unsigned int*			ret;
	/* In&Output Variables */
	unsigned int			i;
	/* Statement Variables*/
	/* Argument Variables */
} binsearch;

#endif // __BINSEARCH_H__