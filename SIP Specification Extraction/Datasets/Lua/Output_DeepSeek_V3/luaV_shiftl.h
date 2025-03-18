#if !defined(__LUAV_SHIFTL_H__)
#define __LUAV_SHIFTL_H__

#include "common.h"


#ifndef _INTOP_
	#define intop(op,v1,v2) l_castU2S(l_castS2U(v1) op l_castS2U(v2))
#endif

#ifndef _LUA_INTEGER_
	typedef int lua_Integer;
#endif

#define NBITS 100

typedef struct __luaV_shiftl
{
/* 接口函数 */
	void (*fun)( struct __luaV_shiftl *);
/* 输入端口 */
	lua_Integer			x;
	lua_Integer			y;
	/* 输出端口 */
	lua_Integer*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} luaV_shiftl;

void luaV_shiftlFun(luaV_shiftl *pIpIp);
#endif // __LUAV_SHIFTL_H__