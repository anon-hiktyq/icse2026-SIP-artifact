#if !defined(__LUAO_UTF8ESC_H__)
#define __LUAO_UTF8ESC_H__

#include "common.h"


#ifndef _LUA_ASSERT_
	#define lua_assert(i) ((void)0)
#endif

#define cast_char(i) ((char) (i))

#define UTF8BUFFSZ 100

typedef struct __luaO_utf8esc
{
/* 接口函数 */
	void (*fun)( struct __luaO_utf8esc *);
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

void luaO_utf8escFun(luaO_utf8esc *pIp);
#endif // __LUAO_UTF8ESC_H__