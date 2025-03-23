#if !defined(__LUAL_BUFFINIT_H__)
#define __LUAL_BUFFINIT_H__

#include "common.h"
#include "lua_pushlightuserdata.h"

#ifndef _LUAL_BUFFERSIZE_
#define _LUAL_BUFFERSIZE_
	#define LUAL_BUFFERSIZE ((int)(16 * sizeof(void*) * sizeof(lua_Number)))
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _luaL_Buffer_
#define _luaL_Buffer_
	struct luaL_Buffer;
#endif


void luaL_buffinitFun(void *p);

typedef struct __luaL_buffinit
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	luaL_Buffer*			B;
	/* Statement Variables*/
	/* Argument Variables */
} luaL_buffinit;

#endif // __LUAL_BUFFINIT_H__