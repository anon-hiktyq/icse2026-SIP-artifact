#if !defined(__LUAL_ERROR_H__)
#define __LUAL_ERROR_H__

#include "common.h"
#include "luaL_where.h"
#include "lua_pushvfstring.h"
#include "lua_concat.h"
#include "lua_error.h"

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif


void luaL_errorFun(void *p);

typedef struct __luaL_error
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	lua_State*			L;
	const char*			fmt;
	/* Statement Variables*/
	/* Argument Variables */
} luaL_error;

#endif // __LUAL_ERROR_H__