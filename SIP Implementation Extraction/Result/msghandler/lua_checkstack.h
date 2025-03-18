#if !defined(__LUA_CHECKSTACK_H__)
#define __LUA_CHECKSTACK_H__

#include "common.h"
#include luaD_growstack.h

#define api_check ((void)(l), lua_assert((e) && msg))
#define lua_lock ((void) 0)
#define lua_unlock ((void) 0)
#ifndef _CALLINFO_
	typedef struct CallInfo CallInfo;
#endif


void lua_checkstackFun(void *p);

typedef struct __lua_checkstack
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			n;
	/* Output Variables */
	int			res;
	int*			ret;
	/* In&Output Variables */
	lua_State*			L;
	/* Statement Variables*/
	/* Argument Variables */
} lua_checkstack;

#endif // __LUA_CHECKSTACK_H__