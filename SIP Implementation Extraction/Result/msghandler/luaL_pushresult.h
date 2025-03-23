#if !defined(__LUAL_PUSHRESULT_H__)
#define __LUAL_PUSHRESULT_H__

#include "common.h"
#include "lua_pushlstring.h"
#include "lua_touserdata.h"
#include "lua_getallocf.h"
#include "resizebox.h"
#include "lua_pushexternalstring.h"
#include "lua_closeslot.h"
#include "lua_gc.h"
#include "lua_settop.h"

#ifndef _LUA_GCSTEP_
#define _LUA_GCSTEP_
	#define LUA_GCSTEP 5
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

#ifndef _lua_Alloc_
#define _lua_Alloc_
	typedef void * (*lua_Alloc) (void *ud, void *ptr, size_t osize, size_t nsize);
#endif

#ifndef _luaL_Buffer_
#define _luaL_Buffer_
	struct luaL_Buffer;
#endif

#ifndef _UBox_
#define _UBox_
	struct UBox {
	  void *box;
	  size_t bsize;
	};
#endif


void luaL_pushresultFun(void *p);

typedef struct __luaL_pushresult
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	luaL_Buffer*			B;
	/* Statement Variables*/
	/* Argument Variables */
} luaL_pushresult;

#endif // __LUAL_PUSHRESULT_H__