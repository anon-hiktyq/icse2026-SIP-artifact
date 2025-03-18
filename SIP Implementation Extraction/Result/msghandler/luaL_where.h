#if !defined(__LUAL_WHERE_H__)
#define __LUAL_WHERE_H__

#include "common.h"
#include lua_getstack.h
#include lua_getinfo.h
#include lua_pushfstring.h
#include lua_pushfstring.h

struct lua_State;
#ifndef _LUA_DEBUG_
	struct lua_Debug;
#endif


void luaL_whereFun(void *p);

typedef struct __luaL_where
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			level;
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	/* Statement Variables*/
	/* Argument Variables */
} luaL_where;

#endif // __LUAL_WHERE_H__