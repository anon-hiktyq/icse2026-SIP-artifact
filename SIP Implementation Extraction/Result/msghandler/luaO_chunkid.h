#if !defined(__LUAO_CHUNKID_H__)
#define __LUAO_CHUNKID_H__

#include "common.h"


#ifndef _LUA_IDSIZE_
#define _LUA_IDSIZE_
	#define LUA_IDSIZE 60
#endif

#ifndef _LL_
#define _LL_
	#define LL (sizeof(x)/sizeof(char) - 1)
#endif

#ifndef _ct_diff2sz_
#define _ct_diff2sz_
	#define ct_diff2sz ((size_t)(df))
#endif

#ifndef _RETS_
#define _RETS_
	#define RETS "..."
#endif

#ifndef _PRE_
#define _PRE_
	#define PRE "[string \""
#endif

#ifndef _POS_
#define _POS_
	#define POS "\"]"
#endif

#ifndef _addstr_
#define _addstr_
	#define addstr ( memcpy(a,b,(l) * sizeof(char)), a += (l) )
#endif


void luaO_chunkidFun(void *p);

typedef struct __luaO_chunkid
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	size_t			srclen;
	/* Output Variables */
	/* In&Output Variables */
	char*			out;
	const char*			source;
	/* Statement Variables*/
	/* Argument Variables */
} luaO_chunkid;

#endif // __LUAO_CHUNKID_H__