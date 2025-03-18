#if !defined(__PUSHFUNCNAME_H__)
#define __PUSHFUNCNAME_H__

#include "common.h"
#include pushglobalfuncname.h
#include lua_pushfstring.h
#include lua_settop.h
#include lua_pushfstring.h
#include lua_pushfstring.h

#ifndef _LUA_PUSHLITERAL_
	#define lua_pushliteral lua_pushstring(L, "" s)
#endif

#define lua_tostring lua_tolstring(L, (i), NULL)
#ifndef _LUA_REMOVE_
	#define lua_remove (lua_rotate(L, (idx), -1), lua_pop(L, 1))
#endif

struct lua_State;
#ifndef _LUA_DEBUG_
	struct lua_Debug;
#endif


void pushfuncnameFun(void *p);

typedef struct __pushfuncname
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	lua_Debug*			ar;
	/* Statement Variables*/
	/* Argument Variables */
} pushfuncname;

#endif // __PUSHFUNCNAME_H__