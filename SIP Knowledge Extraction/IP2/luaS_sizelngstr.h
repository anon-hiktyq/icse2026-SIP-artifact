#if !defined(__LUAS_SIZELNGSTR_H__)
#define __LUAS_SIZELNGSTR_H__

#include "common.h"


#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _LSTRREG_
	#define LSTRREG -1
#endif

#ifndef _LSTRFIX_
	#define LSTRFIX -2
#endif

#ifndef _LSTRMEM_
	#define LSTRMEM -3
#endif


void luaS_sizelngstrFun(void *p);

typedef struct __luaS_sizelngstr
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	size_t			len;
	int			kind;
	/* 输出端口 */
	size_t*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} luaS_sizelngstr;

#endif // __LUAS_SIZELNGSTR_H__