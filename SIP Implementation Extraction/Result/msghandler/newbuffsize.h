#if !defined(__NEWBUFFSIZE_H__)
#define __NEWBUFFSIZE_H__

#include "common.h"


#ifndef _L_UNLIKELY_
	#define l_unlikely luai_unlikely(x)
#endif

#ifndef _MAX_SIZE_
	#define MAX_SIZE (sizeof(size_t) < sizeof(lua_Integer) ? MAX_SIZET \
				  : cast_sizet(LUA_MAXINTEGER))
#endif

#ifndef _CAST_SIZET_
	#define cast_sizet cast(size_t, (i))
#endif

struct lua_State;
#ifndef _LUAL_BUFFER_
	struct luaL_Buffer;
#endif


void newbuffsizeFun(void *p);

typedef struct __newbuffsize
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	size_t			sz;
	/* Output Variables */
	size_t*			ret;
	/* In&Output Variables */
	luaL_Buffer*			B;
	/* Statement Variables*/
	/* Argument Variables */
} newbuffsize;

#endif // __NEWBUFFSIZE_H__