#if !defined(__LASTLEVEL_H__)
#define __LASTLEVEL_H__

#include "common.h"
#include lua_getstack.h
#include lua_getstack.h

struct lua_State;
#ifndef _LUA_DEBUG_
	struct lua_Debug;
#endif


void lastlevelFun(void *p);

typedef struct __lastlevel
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	lua_State*			L;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} lastlevel;

#endif // __LASTLEVEL_H__