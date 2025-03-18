#if !defined(__COUNTINT_H__)
#define __COUNTINT_H__

#include "common.h"
#include luaO_ceillog2.h

#ifndef _ARRAYINDEX_
	#define arrayindex checkrange(k, MAXASIZE)
#endif

#ifndef _LUA_INTEGER_
	typedef LUA_INTEGER lua_Integer;
#endif

#ifndef _COUNTERS_
	struct {
	  unsigned total;
	  unsigned na;
	  int deleted;
	  unsigned nums[MAXABITS + 1];
	};
#endif


void countintFun(void *p);

typedef struct __countint
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	lua_Integer			key;
	/* 输出端口 */
	/* 输入输出端口 */
	Counters*			ct;
	/* 状态变量 */
	/* 参数变量 */
} countint;

#endif // __COUNTINT_H__