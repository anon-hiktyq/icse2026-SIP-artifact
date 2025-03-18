#if !defined(__LUAV_TOINTEGER_H__)
#define __LUAV_TOINTEGER_H__

#include "common.h"
#include l_strton.h
#include luaV_tointegerns.h

#ifndef _LUA_INTEGER_
	typedef LUA_INTEGER lua_Integer;
#endif

#ifndef _TVALUE_
	struct TValue {
	  TValuefields;
	};
#endif

#ifndef _F2IMOD_
	enum {
	  F2Ieq,     /* no rounding; accepts only integral values */
	  F2Ifloor,  /* takes the floor of the number */
	  F2Iceil    /* takes the ceiling of the number */
	};
#endif


void luaV_tointegerFun(void *p);

typedef struct __luaV_tointeger
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	F2Imod			mode;
	/* 输出端口 */
	int*			ret;
	/* 输入输出端口 */
	const TValue*			obj;
	lua_Integer*			p;
	/* 状态变量 */
	/* 参数变量 */
} luaV_tointeger;

#endif // __LUAV_TOINTEGER_H__