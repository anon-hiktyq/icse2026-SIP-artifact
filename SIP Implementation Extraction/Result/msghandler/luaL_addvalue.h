#if !defined(__LUAL_ADDVALUE_H__)
#define __LUAL_ADDVALUE_H__

#include "common.h"
#include "lua_tolstring.h"
#include "prepbuffsize.h"

#ifndef _lua_pop_
#define _lua_pop_
	#define lua_pop lua_settop(L, -(n)-1)
#endif

#ifndef _luaL_addsize_
#define _luaL_addsize_
	#define luaL_addsize ((B)->n += (s))
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _luaL_Buffer_
#define _luaL_Buffer_
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