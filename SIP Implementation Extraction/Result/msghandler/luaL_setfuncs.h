#if !defined(__LUAL_SETFUNCS_H__)
#define __LUAL_SETFUNCS_H__

#include "common.h"
#include "luaL_checkstack.h"
#include "lua_pushboolean.h"
#include "lua_pushvalue.h"
#include "lua_pushcclosure.h"
#include "lua_setfield.h"

#ifndef _lua_pop_
#define _lua_pop_
	#define lua_pop lua_settop(L, -(n)-1)
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _lua_CFunction_
#define _lua_CFunction_
	typedef int (*lua_CFunction) (lua_State *L);
#endif

#ifndef _luaL_Reg_
#define _luaL_Reg_
	struct luaL_Reg {
	  const char *name;
	  lua_CFunction func;
	};
#endif


void luaL_setfuncsFun(void *p);

typedef struct __luaL_setfuncs
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const luaL_Reg*			l;
	int			nup;
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	/* Statement Variables*/
	/* Argument Variables */
} luaL_setfuncs;

#endif // __LUAL_SETFUNCS_H__