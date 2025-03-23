#if !defined(__PUSHGLOBALFUNCNAME_H__)
#define __PUSHGLOBALFUNCNAME_H__

#include "common.h"
#include "lua_gettop.h"
#include "lua_getinfo.h"
#include "lua_getfield.h"
#include "luaL_checkstack.h"
#include "findfield.h"
#include "lua_pushstring.h"
#include "lua_settop.h"
#include "lua_copy.h"

#ifndef _LUA_REGISTRYINDEX_
#define _LUA_REGISTRYINDEX_
	#define LUA_REGISTRYINDEX (-LUAI_MAXSTACK - 1000)
#endif

#ifndef _lua_tostring_
#define _lua_tostring_
	#define lua_tostring lua_tolstring(L, (i), NULL)
#endif

#ifndef _lua_remove_
#define _lua_remove_
	#define lua_remove (lua_rotate(L, (idx), -1), lua_pop(L, 1))
#endif

#ifndef _LUA_GNAME_
#define _LUA_GNAME_
	#define LUA_GNAME "_G"
#endif

#ifndef _LUA_LOADED_TABLE_
#define _LUA_LOADED_TABLE_
	#define LUA_LOADED_TABLE "_LOADED"
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _lua_Debug_
#define _lua_Debug_
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