#if !defined(__PREPBUFFSIZE_H__)
#define __PREPBUFFSIZE_H__

#include "common.h"
#include "newbuffsize.h"
#include "resizebox.h"
#include "lua_settop.h"
#include "newbox.h"
#include "lua_toclose.h"

#ifndef _lua_insert_
#define _lua_insert_
	#define lua_insert lua_rotate(L, (idx), 1)
#endif

#ifndef _lua_remove_
#define _lua_remove_
	#define lua_remove (lua_rotate(L, (idx), -1), lua_pop(L, 1))
#endif

#ifndef _buffonstack_
#define _buffonstack_
	#define buffonstack ((B)->b != (B)->init.b)
#endif

#ifndef _checkbufferlevel_
#define _checkbufferlevel_
	#define checkbufferlevel lua_assert(buffonstack(B) ? lua_touserdata(B->L, idx) != NULL  \
	                            : lua_touserdata(B->L, idx) == (void*)B)
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _luaL_Buffer_
#define _luaL_Buffer_
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