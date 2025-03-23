#if !defined(__LUAL_NEWMETATABLE_H__)
#define __LUAL_NEWMETATABLE_H__

#include "common.h"
#include "lua_settop.h"
#include "lua_createtable.h"
#include "lua_pushstring.h"
#include "lua_setfield.h"
#include "lua_pushvalue.h"

#ifndef _LUA_REGISTRYINDEX_
#define _LUA_REGISTRYINDEX_
	#define LUA_REGISTRYINDEX (-LUAI_MAXSTACK - 1000)
#endif

#ifndef _LUA_TNIL_
#define _LUA_TNIL_
	#define LUA_TNIL 0
#endif

#ifndef _lua_pop_
#define _lua_pop_
	#define lua_pop lua_settop(L, -(n)-1)
#endif

#ifndef _luaL_getmetatable_
#define _luaL_getmetatable_
	#define luaL_getmetatable (lua_getfield(L, LUA_REGISTRYINDEX, (n)))
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif


void luaL_newmetatableFun(void *p);

typedef struct __luaL_newmetatable
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	lua_State*			L;
	const char*			tname;
	/* Statement Variables*/
	/* Argument Variables */
} luaL_newmetatable;

#endif // __LUAL_NEWMETATABLE_H__