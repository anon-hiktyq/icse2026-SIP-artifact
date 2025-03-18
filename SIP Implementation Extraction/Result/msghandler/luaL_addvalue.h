#if !defined(__LUAL_ADDVALUE_H__)
#define __LUAL_ADDVALUE_H__

#include "common.h"
#include lua_tolstring.h
#include prepbuffsize.h

#ifndef _LUA_POP_
	#define lua_pop lua_settop(L, -(n)-1)
#endif

#ifndef _LUAL_ADDSIZE_
	#define luaL_addsize ((B)->n += (s))
#endif

struct lua_State;
#ifndef _LUAL_BUFFER_
	struct luaL_Buffer;
#endif


void luaL_addvalueFun(void *p);

typedef struct __luaL_addvalue
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	luaL_Buffer*			B;
	/* Statement Variables*/
	/* Argument Variables */
} luaL_addvalue;

#endif // __LUAL_ADDVALUE_H__