#if !defined(__LUAL_ADDSTRING_H__)
#define __LUAL_ADDSTRING_H__

#include "common.h"
#include luaL_addlstring.h

#ifndef _LUAL_BUFFER_
	struct luaL_Buffer;
#endif


void luaL_addstringFun(void *p);

typedef struct __luaL_addstring
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	luaL_Buffer*			B;
	const char*			s;
	/* Statement Variables*/
	/* Argument Variables */
} luaL_addstring;

#endif // __LUAL_ADDSTRING_H__