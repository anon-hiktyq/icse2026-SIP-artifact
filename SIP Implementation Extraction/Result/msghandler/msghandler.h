#if !defined(__MSGHANDLER_H__)
#define __MSGHANDLER_H__

#include "common.h"
#include luaL_callmeta.h
#include lua_type.h
#include lua_pushfstring.h
#include luaL_traceback.h

#define LUA_TSTRING 4
#define lua_tostring lua_tolstring(L, (i), NULL)
#define luaL_typename lua_typename(L, lua_type(L,(i)))

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