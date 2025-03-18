#if !defined(__LUAL_CHECKSTACK_H__)
#define __LUAL_CHECKSTACK_H__

#include "common.h"
#include luaL_error.h
#include luaL_error.h

#ifndef _L_UNLIKELY_
	#define l_unlikely luai_unlikely(x)
#endif

struct lua_State;

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