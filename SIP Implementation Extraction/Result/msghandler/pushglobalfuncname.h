#if !defined(__PUSHGLOBALFUNCNAME_H__)
#define __PUSHGLOBALFUNCNAME_H__

#include "common.h"
#include lua_gettop.h
#include lua_getinfo.h
#include lua_getfield.h
#include luaL_checkstack.h
#include findfield.h
#include lua_pushstring.h
#include lua_settop.h
#include lua_copy.h
#include lua_settop.h
#include lua_settop.h

#ifndef _LUA_REGISTRYINDEX_
	#define LUA_REGISTRYINDEX (-LUAI_MAXSTACK - 1000)
#endif

#define lua_tostring lua_tolstring(L, (i), NULL)
#ifndef _LUA_REMOVE_
	#define lua_remove (lua_rotate(L, (idx), -1), lua_pop(L, 1))
#endif

#ifndef _LUA_GNAME_
	#define LUA_GNAME "_G"
#endif

#ifndef _LUA_LOADED_TABLE_
	#define LUA_LOADED_TABLE "_LOADED"
#endif

struct lua_State;
#ifndef _LUA_DEBUG_
	struct lua_Debug;
#endif


void pushglobalfuncnameFun(void *p);

typedef struct __pushglobalfuncname
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	lua_State*			L;
	lua_Debug*			ar;
	/* Statement Variables*/
	/* Argument Variables */
} pushglobalfuncname;

#endif // __PUSHGLOBALFUNCNAME_H__