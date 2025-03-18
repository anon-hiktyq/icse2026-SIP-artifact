#if !defined(__LUAO_HEXAVALUE_H__)
#define __LUAO_HEXAVALUE_H__

#include "common.h"
#include "ctype.h"

#ifndef _LUA_ASSERT_
	#define lua_assert(p) ((void)p)
#endif

#ifndef _CAST_BYTE_
	#define cast_byte(i) ((lu_byte)(i))
#endif

#ifndef _LISDIGIT_
	#define lisdigit(c) (isdigit(c))
#endif

#ifndef _LISXDIGIT_
	#define lisxdigit(c) (isxdigit(c))
#endif

#ifndef _LTOLOWER_
	#define ltolower(c) (tolower(c))
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif



typedef struct __luaO_hexavalue
{
/* 接口函数 */
	void (*fun)( struct __luaO_hexavalue *);
/* 输入端口 */
	int			c;
	/* 输出端口 */
	lu_byte*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} luaO_hexavalue;

void luaO_hexavalueFun(luaO_hexavalue *pIp);
#endif // __LUAO_HEXAVALUE_H__