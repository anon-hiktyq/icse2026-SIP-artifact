#if !defined(__LUAV_TOINTEGER_H__)
#define __LUAV_TOINTEGER_H__

#include "common.h"
#include "l_strton.h"
#include "luaV_tointegerns.h"

#ifndef _lua_Integer_
#define _lua_Integer_
	typedef LUA_INTEGER lua_Integer;
#endif

#ifndef _TValue_
#define _TValue_
	struct TValue {
	  TValuefields;
	};
#endif

#ifndef _F2Imod_
#define _F2Imod_
	enum {
	  F2Ieq,     /* no rounding; accepts only integral values */
	  F2Ifloor,  /* takes the floor of the number */
	  F2Iceil    /* takes the ceiling of the number */
	};
#endif


void luaV_tointegerFun(void *p);

typedef struct __luaV_tointeger
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	F2Imod			mode;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	const TValue*			obj;
	lua_Integer*			p;
	/* Statement Variables*/
	/* Argument Variables */
} luaV_tointeger;

#endif // __LUAV_TOINTEGER_H__