#if !defined(__PREPBUFFSIZE_H__)
#define __PREPBUFFSIZE_H__

#include "common.h"
#include newbuffsize.h
#include resizebox.h
#include lua_settop.h
#include newbox.h
#include lua_toclose.h
#include resizebox.h

#ifndef _LUA_INSERT_
	#define lua_insert lua_rotate(L, (idx), 1)
#endif

#ifndef _LUA_REMOVE_
	#define lua_remove (lua_rotate(L, (idx), -1), lua_pop(L, 1))
#endif

#ifndef _BUFFONSTACK_
	#define buffonstack ((B)->b != (B)->init.b)
#endif

#ifndef _CHECKBUFFERLEVEL_
	#define checkbufferlevel lua_assert(buffonstack(B) ? lua_touserdata(B->L, idx) != NULL  \
	                            : lua_touserdata(B->L, idx) == (void*)B)
#endif

struct lua_State;
#ifndef _LUAL_BUFFER_
	struct luaL_Buffer;
#endif


void prepbuffsizeFun(void *p);

typedef struct __prepbuffsize
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	size_t			sz;
	int			boxidx;
	/* Output Variables */
	char *			ret;
	/* In&Output Variables */
	luaL_Buffer*			B;
	/* Statement Variables*/
	/* Argument Variables */
} prepbuffsize;

#endif // __PREPBUFFSIZE_H__