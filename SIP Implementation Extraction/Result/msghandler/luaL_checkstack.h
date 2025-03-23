#if !defined(__LUAL_CHECKSTACK_H__)
#define __LUAL_CHECKSTACK_H__

#include "common.h"
#include "luaL_error.h"

#ifndef _l_unlikely_
#define _l_unlikely_
	#define l_unlikely luai_unlikely(x)
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif


void luaL_checkstackFun(void *p);

typedef struct __luaL_checkstack
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			space;
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	const char*			msg;
	/* Statement Variables*/
	/* Argument Variables */
} luaL_checkstack;

#endif // __LUAL_CHECKSTACK_H__