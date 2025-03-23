#if !defined(__LUAL_CALLMETA_H__)
#define __LUAL_CALLMETA_H__

#include "common.h"
#include "lua_absindex.h"
#include "luaL_getmetafield.h"
#include "lua_pushvalue.h"

#ifndef _LUA_TNIL_
#define _LUA_TNIL_
	#define LUA_TNIL 0
#endif

#ifndef _lua_call_
#define _lua_call_
	#define lua_call lua_callk(L, (n), (r), 0, NULL)
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _lua_KContext_
#define _lua_KContext_
	typedef LUA_KCONTEXT lua_KContext;
#endif

#ifndef _lua_KFunction_
#define _lua_KFunction_
	typedef int (*lua_KFunction) (lua_State *L, int status, lua_KContext ctx);
#endif


void luaL_callmetaFun(void *p);

typedef struct __luaL_callmeta
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			obj;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	lua_State*			L;
	const char*			event;
	/* Statement Variables*/
	/* Argument Variables */
} luaL_callmeta;

#endif // __LUAL_CALLMETA_H__