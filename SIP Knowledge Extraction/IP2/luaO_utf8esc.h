#if !defined(__LUAO_UTF8ESC_H__)
#define __LUAO_UTF8ESC_H__

#include "common.h"


#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#define cast_char cast(char, (i))
#ifndef _UTF8BUFFSZ_
	#define UTF8BUFFSZ 8
#endif


void luaO_utf8escFun(void *p);

typedef struct __luaO_utf8esc
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	unsigned long			x;
	/* 输出端口 */
	int			n;
	int*			ret;
	/* 输入输出端口 */
	char*			buff;
	/* 状态变量 */
	/* 参数变量 */
} luaO_utf8esc;

#endif // __LUAO_UTF8ESC_H__