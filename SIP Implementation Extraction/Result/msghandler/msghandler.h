#if !defined(__MSGHANDLER_H__)
#define __MSGHANDLER_H__

#include "common.h"
#include "luaL_callmeta.h"
#include "lua_type.h"
#include "lua_pushfstring.h"
#include "luaL_traceback.h"

#ifndef _LUA_TSTRING_
#define _LUA_TSTRING_
	#define LUA_TSTRING 4
#endif

#ifndef _lua_tostring_
#define _lua_tostring_
	#define lua_tostring lua_tolstring(L, (i), NULL)
#endif

#ifndef _luaL_typename_
#define _luaL_typename_
	#define luaL_typename lua_typename(L, lua_type(L,(i)))
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif


void msghandlerFun(void *p);

typedef struct __msghandler
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
} msghandler;

#endif // __MSGHANDLER_H__