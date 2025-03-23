#if !defined(__LASTLEVEL_H__)
#define __LASTLEVEL_H__

#include "common.h"
#include "lua_getstack.h"

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _lua_Debug_
#define _lua_Debug_
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