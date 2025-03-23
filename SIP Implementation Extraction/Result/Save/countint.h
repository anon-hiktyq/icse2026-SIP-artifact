#if !defined(__COUNTINT_H__)
#define __COUNTINT_H__

#include "common.h"
#include "luaO_ceillog2.h"

#ifndef _arrayindex_
#define _arrayindex_
	#define arrayindex checkrange(k, MAXASIZE)
#endif

#ifndef _lua_Integer_
#define _lua_Integer_
	typedef LUA_INTEGER lua_Integer;
#endif

#ifndef _Counters_
#define _Counters_
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
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	lua_Integer			key;
	/* Output Variables */
	/* In&Output Variables */
	Counters*			ct;
	/* Statement Variables*/
	/* Argument Variables */
} countint;

#endif // __COUNTINT_H__