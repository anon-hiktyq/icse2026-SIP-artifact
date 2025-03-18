#if !defined(__LUAL_NEWMETATABLE_H__)
#define __LUAL_NEWMETATABLE_H__

#include "common.h"
#include lua_settop.h
#include lua_createtable.h
#include lua_pushstring.h
#include lua_setfield.h
#include lua_pushvalue.h
#include lua_setfield.h

#ifndef _LUA_REGISTRYINDEX_
	#define LUA_REGISTRYINDEX (-LUAI_MAXSTACK - 1000)
#endif

#ifndef _LUA_TNIL_
	#define LUA_TNIL 0
#endif

#ifndef _LUA_POP_
	#define lua_pop lua_settop(L, -(n)-1)
#endif

#ifndef _LUAL_GETMETATABLE_
	#define luaL_getmetatable (lua_getfield(L, LUA_REGISTRYINDEX, (n)))
#endif

struct lua_State;

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