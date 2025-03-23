#if !defined(__LUAL_ADDLSTRING_H__)
#define __LUAL_ADDLSTRING_H__

#include "common.h"
#include "prepbuffsize.h"

#ifndef _luaL_addsize_
#define _luaL_addsize_
	#define luaL_addsize ((B)->n += (s))
#endif

#ifndef _luaL_Buffer_
#define _luaL_Buffer_
	struct luaL_Buffer;
#endif


void luaL_addlstringFun(void *p);

typedef struct __luaL_addlstring
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	size_t			l;
	/* Output Variables */
	/* In&Output Variables */
	luaL_Buffer*			B;
	const char*			s;
	/* Statement Variables*/
	/* Argument Variables */
} luaL_addlstring;

#endif // __LUAL_ADDLSTRING_H__