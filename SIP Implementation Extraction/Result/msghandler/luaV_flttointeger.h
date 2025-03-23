#if !defined(__LUAV_FLTTOINTEGER_H__)
#define __LUAV_FLTTOINTEGER_H__

#include "common.h"


#ifndef _l_floor_
#define _l_floor_
	#define l_floor (l_mathop(floor)(x))
#endif

#ifndef _lua_numbertointeger_
#define _lua_numbertointeger_
	#define lua_numbertointeger ((n) >= (LUA_NUMBER)(LUA_MININTEGER) && \
	   (n) < -(LUA_NUMBER)(LUA_MININTEGER) && \
	      (*(p) = (LUA_INTEGER)(n), 1))
#endif

#ifndef _lua_Number_
#define _lua_Number_
	typedef LUA_NUMBER lua_Number;
#endif

#ifndef _lua_Integer_
#define _lua_Integer_
	typedef LUA_INTEGER lua_Integer;
#endif

#ifndef _F2Imod_
#define _F2Imod_
	enum {
	  F2Ieq,     /* no rounding; accepts only integral values */
	  F2Ifloor,  /* takes the floor of the number */
	  F2Iceil    /* takes the ceiling of the number */
	};
#endif


void luaV_flttointegerFun(void *p);

typedef struct __luaV_flttointeger
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	lua_Number			n;
	F2Imod			mode;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	lua_Integer*			p;
	/* Statement Variables*/
	/* Argument Variables */
} luaV_flttointeger;

#endif // __LUAV_FLTTOINTEGER_H__