#if !defined(__PANIC_H__)
#define __PANIC_H__

#include "common.h"
#include lua_type.h

#define LUA_TSTRING 4
#define lua_tostring lua_tolstring(L, (i), NULL)
#ifndef _LUA_WRITESTRINGERROR_
	#define lua_writestringerror (fprintf(stderr, (s), (p)), fflush(stderr))
#endif

struct lua_State;

void panicFun(void *p);

typedef struct __panic
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	lua_State*			L;
	/* Statement Variables*/
	/* Argument Variables */
} panic;

#endif // __PANIC_H__