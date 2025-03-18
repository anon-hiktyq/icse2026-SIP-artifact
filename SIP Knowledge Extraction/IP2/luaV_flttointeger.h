#if !defined(__LUAV_FLTTOINTEGER_H__)
#define __LUAV_FLTTOINTEGER_H__

#include "common.h"


#ifndef _L_FLOOR_
	#define l_floor (l_mathop(floor)(x))
#endif

#ifndef _LUA_NUMBERTOINTEGER_
	#define lua_numbertointeger ((n) >= (LUA_NUMBER)(LUA_MININTEGER) && \
	   (n) < -(LUA_NUMBER)(LUA_MININTEGER) && \
	      (*(p) = (LUA_INTEGER)(n), 1))
#endif

#ifndef _LUA_NUMBER_
	typedef LUA_NUMBER lua_Number;
#endif

#ifndef _LUA_INTEGER_
	typedef LUA_INTEGER lua_Integer;
#endif

#ifndef _F2IMOD_
	enum {
	  F2Ieq,     /* no rounding; accepts only integral values */
	  F2Ifloor,  /* takes the floor of the number */
	  F2Iceil    /* takes the ceiling of the number */
	};
#endif


void luaV_flttointegerFun(void *p);

typedef struct __luaV_flttointeger
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	lua_Number			n;
	F2Imod			mode;
	/* 输出端口 */
	int*			ret;
	/* 输入输出端口 */
	lua_Integer*			p;
	/* 状态变量 */
	/* 参数变量 */
} luaV_flttointeger;

#endif // __LUAV_FLTTOINTEGER_H__