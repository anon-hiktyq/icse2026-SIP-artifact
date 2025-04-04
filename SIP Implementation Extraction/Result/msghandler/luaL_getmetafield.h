#if !defined(__LUAL_GETMETAFIELD_H__)
#define __LUAL_GETMETAFIELD_H__

#include "common.h"
#include "lua_getmetatable.h"
#include "lua_pushstring.h"
#include "lua_rawget.h"
#include "lua_rotate.h"

#ifndef _LUA_TNIL_
#define _LUA_TNIL_
	#define LUA_TNIL 0
#endif

#ifndef _lua_pop_
#define _lua_pop_
	#define lua_pop lua_settop(L, -(n)-1)
#endif

#ifndef _lua_remove_
#define _lua_remove_
	#define lua_remove (lua_rotate(L, (idx), -1), lua_pop(L, 1))
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif


void luaL_getmetafieldFun(void *p);

typedef struct __luaL_getmetafield
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
} luaL_getmetafield;

#endif // __LUAL_GETMETAFIELD_H__