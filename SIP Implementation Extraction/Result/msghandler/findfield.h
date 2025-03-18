#if !defined(__FINDFIELD_H__)
#define __FINDFIELD_H__

#include "common.h"
#include lua_pushnil.h
#include lua_next.h
#include lua_type.h
#include lua_rawequal.h
#include findfield.h
#include lua_copy.h
#include lua_concat.h

#define LUA_TSTRING 4
#ifndef _LUA_POP_
	#define lua_pop lua_settop(L, -(n)-1)
#endif

#ifndef _LUA_ISTABLE_
	#define lua_istable (lua_type(L, (n)) == LUA_TTABLE)
#endif

#ifndef _LUA_PUSHLITERAL_
	#define lua_pushliteral lua_pushstring(L, "" s)
#endif

#ifndef _LUA_REPLACE_
	#define lua_replace (lua_copy(L, -1, (idx)), lua_pop(L, 1))
#endif

struct lua_State;

void findfieldFun(void *p);

typedef struct __findfield
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			objidx;
	int			level;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	lua_State*			L;
	/* Statement Variables*/
	/* Argument Variables */
} findfield;

#endif // __FINDFIELD_H__