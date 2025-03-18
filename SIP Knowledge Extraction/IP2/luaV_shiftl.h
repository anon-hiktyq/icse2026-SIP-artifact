#if !defined(__LUAV_SHIFTL_H__)
#define __LUAV_SHIFTL_H__

#include "common.h"


#ifndef _INTOP_
	#define intop l_castU2S(l_castS2U(v1) op l_castS2U(v2))
#endif

#ifndef _NBITS_
	#define NBITS cast_int(sizeof(lua_Integer) * CHAR_BIT)
#endif

#ifndef _LUA_INTEGER_
	typedef LUA_INTEGER lua_Integer;
#endif


void luaV_shiftlFun(void *p);

typedef struct __luaV_shiftl
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	lua_Integer			x;
	lua_Integer			y;
	/* 输出端口 */
	lua_Integer*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} luaV_shiftl;

#endif // __LUAV_SHIFTL_H__