#if !defined(__LUAL_TRACEBACK_H__)
#define __LUAL_TRACEBACK_H__

#include "common.h"
#include "lastlevel.h"
#include "luaL_buffinit.h"
#include "luaL_addstring.h"
#include "lua_getstack.h"
#include "lua_pushfstring.h"
#include "luaL_addvalue.h"
#include "lua_getinfo.h"
#include "pushfuncname.h"
#include "luaL_pushresult.h"

#ifndef _luaL_addchar_
#define _luaL_addchar_
	#define luaL_addchar ((void)((B)->n < (B)->size || luaL_prepbuffsize((B), 1)), \
	   ((B)->b[(B)->n++] = (c)))
#endif

#ifndef _LEVELS1_
#define _LEVELS1_
	#define LEVELS1 10
#endif

#ifndef _LEVELS2_
#define _LEVELS2_
	#define LEVELS2 11
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _lua_Debug_
#define _lua_Debug_
	struct lua_Debug;
#endif

#ifndef _luaL_Buffer_
#define _luaL_Buffer_
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