#if !defined(__LUAL_CALLMETA_H__)
#define __LUAL_CALLMETA_H__

#include "common.h"
#include lua_absindex.h
#include luaL_getmetafield.h
#include lua_pushvalue.h

#ifndef _LUA_TNIL_
	#define LUA_TNIL 0
#endif

#ifndef _LUA_CALL_
	#define lua_call lua_callk(L, (n), (r), 0, NULL)
#endif

struct lua_State;
#ifndef _LUA_KCONTEXT_
	typedef LUA_KCONTEXT lua_KContext;
#endif

#ifndef _LUA_KFUNCTION_
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