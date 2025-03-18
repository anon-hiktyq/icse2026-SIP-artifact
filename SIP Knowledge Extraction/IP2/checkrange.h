#if !defined(__CHECKRANGE_H__)
#define __CHECKRANGE_H__

#include "common.h"


#ifndef _CAST_UINT_
	#define cast_uint cast(unsigned int, (i))
#endif

#ifndef _L_CASTS2U_
	#define l_castS2U ((lua_Unsigned)(i))
#endif

#ifndef _LUA_INTEGER_
	typedef LUA_INTEGER lua_Integer;
#endif


void checkrangeFun(void *p);

typedef struct __checkrange
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	lua_Integer			k;
	unsigned int			limit;
	/* 输出端口 */
	unsigned int*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} checkrange;

#endif // __CHECKRANGE_H__