#if !defined(__LUAL_PREPBUFFSIZE_H__)
#define __LUAL_PREPBUFFSIZE_H__

#include "common.h"
#include prepbuffsize.h

#ifndef _LUAL_BUFFER_
	struct luaL_Buffer;
#endif


void luaL_prepbuffsizeFun(void *p);

typedef struct __luaL_prepbuffsize
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	size_t			sz;
	/* Output Variables */
	char *			ret;
	/* In&Output Variables */
	luaL_Buffer*			B;
	/* Statement Variables*/
	/* Argument Variables */
} luaL_prepbuffsize;

#endif // __LUAL_PREPBUFFSIZE_H__