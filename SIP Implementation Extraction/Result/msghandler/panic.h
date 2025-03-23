#if !defined(__PANIC_H__)
#define __PANIC_H__

#include "common.h"
#include "lua_type.h"

#ifndef _LUA_TSTRING_
#define _LUA_TSTRING_
	#define LUA_TSTRING 4
#endif

#ifndef _lua_tostring_
#define _lua_tostring_
	#define lua_tostring lua_tolstring(L, (i), NULL)
#endif

#ifndef _lua_writestringerror_
#define _lua_writestringerror_
	#define lua_writestringerror (fprintf(stderr, (s), (p)), fflush(stderr))
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif


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