#if !defined(__LUAL_TRACEBACK_H__)
#define __LUAL_TRACEBACK_H__

#include "common.h"
#include lastlevel.h
#include luaL_buffinit.h
#include luaL_addstring.h
#include luaL_addstring.h
#include lua_getstack.h
#include lua_pushfstring.h
#include luaL_addvalue.h
#include lua_getinfo.h
#include lua_pushfstring.h
#include lua_pushfstring.h
#include luaL_addvalue.h
#include pushfuncname.h
#include luaL_addvalue.h
#include luaL_addstring.h
#include luaL_pushresult.h

#ifndef _LUAL_ADDCHAR_
	#define luaL_addchar ((void)((B)->n < (B)->size || luaL_prepbuffsize((B), 1)), \
	   ((B)->b[(B)->n++] = (c)))
#endif

#ifndef _LEVELS1_
	#define LEVELS1 10
#endif

#ifndef _LEVELS2_
	#define LEVELS2 11
#endif

struct lua_State;
#ifndef _LUA_DEBUG_
	struct lua_Debug;
#endif

#ifndef _LUAL_BUFFER_
	struct luaL_Buffer;
#endif


void luaL_tracebackFun(void *p);

typedef struct __luaL_traceback
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			level;
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	lua_State*			L1;
	const char*			msg;
	/* Statement Variables*/
	/* Argument Variables */
} luaL_traceback;

#endif // __LUAL_TRACEBACK_H__