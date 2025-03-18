#if !defined(__LUAO_HEXAVALUE_H__)
#define __LUAO_HEXAVALUE_H__

#include "common.h"


#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _CAST_BYTE_
	#define cast_byte cast(lu_byte, (i))
#endif

#ifndef _LISDIGIT_
	#define lisdigit (isdigit(c))
#endif

#ifndef _LISXDIGIT_
	#define lisxdigit (isxdigit(c))
#endif

#ifndef _LTOLOWER_
	#define ltolower (tolower(c))
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif


void luaO_hexavalueFun(void *p);

typedef struct __luaO_hexavalue
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	int			c;
	/* 输出端口 */
	lu_byte*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} luaO_hexavalue;

#endif // __LUAO_HEXAVALUE_H__