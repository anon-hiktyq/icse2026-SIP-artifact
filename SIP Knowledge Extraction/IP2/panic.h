#if !defined(__PANIC_H__)
#define __PANIC_H__

#include "common.h"
#include lua_type.h

#ifndef _LUA_TSTRING_
	#define LUA_TSTRING 4
#endif

#ifndef _LUA_TOSTRING_
	#define lua_tostring lua_tolstring(L, (i), NULL)
#endif

#ifndef _LUA_WRITESTRINGERROR_
	#define lua_writestringerror (fprintf(stderr, (s), (p)), fflush(stderr))
#endif

struct lua_State;

void panicFun(void *p);

typedef struct __panic
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	/* 输出端口 */
	int*			ret;
	/* 输入输出端口 */
	lua_State*			L;
	/* 状态变量 */
	/* 参数变量 */
} panic;

#endif // __PANIC_H__