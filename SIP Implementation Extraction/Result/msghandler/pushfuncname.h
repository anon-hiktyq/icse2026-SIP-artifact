#if !defined(__PUSHFUNCNAME_H__)
#define __PUSHFUNCNAME_H__

#include "common.h"
#include "pushglobalfuncname.h"
#include "lua_pushfstring.h"
#include "lua_settop.h"

#ifndef _lua_pushliteral_
#define _lua_pushliteral_
	#define lua_pushliteral lua_pushstring(L, "" s)
#endif

#ifndef _lua_tostring_
#define _lua_tostring_
	#define lua_tostring lua_tolstring(L, (i), NULL)
#endif

#ifndef _lua_remove_
#define _lua_remove_
	#define lua_remove (lua_rotate(L, (idx), -1), lua_pop(L, 1))
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _lua_Debug_
#define _lua_Debug_
	struct lua_Debug;
#endif


void pushfuncnameFun(void *p);

typedef struct __pushfuncname
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	lua_Debug*			ar;
	/* Statement Variables*/
	/* Argument Variables */
} pushfuncname;

#endif // __PUSHFUNCNAME_H__