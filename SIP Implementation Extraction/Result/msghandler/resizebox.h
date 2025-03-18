#if !defined(__RESIZEBOX_H__)
#define __RESIZEBOX_H__

#include "common.h"
#include lua_touserdata.h
#include lua_getallocf.h
#include lua_error.h

#ifndef _L_UNLIKELY_
	#define l_unlikely luai_unlikely(x)
#endif

#ifndef _LUA_PUSHLITERAL_
	#define lua_pushliteral lua_pushstring(L, "" s)
#endif

struct lua_State;
#ifndef _LUA_ALLOC_
	typedef void * (*lua_Alloc) (void *ud, void *ptr, size_t osize, size_t nsize);
#endif

#ifndef _UBOX_
	struct UBox {
	  void *box;
	  size_t bsize;
	};
#endif


void resizeboxFun(void *p);

typedef struct __resizebox
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			idx;
	size_t			newsize;
	/* Output Variables */
	void *			ret;
	/* In&Output Variables */
	lua_State*			L;
	/* Statement Variables*/
	/* Argument Variables */
} resizebox;

#endif // __RESIZEBOX_H__