#if !defined(__LEFLOATINT_H__)
#define __LEFLOATINT_H__

#include "common.h"
#include luaV_flttointeger.h

#ifndef _CAST_NUM_
	#define cast_num cast(lua_Number, (i))
#endif

#ifndef _LUAI_NUMLE_
	#define luai_numle ((a)<=(b))
#endif

#ifndef _L_INTFITSF_
	#define l_intfitsf 1
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


void LEfloatintFun(void *p);

typedef struct __LEfloatint
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	lua_Number			f;
	lua_Integer			i;
	/* 输出端口 */
	int*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} LEfloatint;

#endif // __LEFLOATINT_H__