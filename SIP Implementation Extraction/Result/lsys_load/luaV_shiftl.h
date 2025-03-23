#if !defined(__LUAV_SHIFTL_H__)
#define __LUAV_SHIFTL_H__

#include "common.h"


#ifndef _intop_
#define _intop_
	#define intop l_castU2S(l_castS2U(v1) op l_castS2U(v2))
#endif

#ifndef _NBITS_
#define _NBITS_
	#define NBITS cast_int(sizeof(lua_Integer) * CHAR_BIT)
#endif

#ifndef _lua_Integer_
#define _lua_Integer_
	typedef LUA_INTEGER lua_Integer;
#endif


void luaV_shiftlFun(void *p);

typedef struct __luaV_shiftl
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	lua_Integer			x;
	lua_Integer			y;
	/* Output Variables */
	lua_Integer*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} luaV_shiftl;

#endif // __LUAV_SHIFTL_H__