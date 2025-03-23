#if !defined(__RESIZEBOX_H__)
#define __RESIZEBOX_H__

#include "common.h"
#include "lua_touserdata.h"
#include "lua_getallocf.h"
#include "lua_error.h"

#ifndef _l_unlikely_
#define _l_unlikely_
	#define l_unlikely luai_unlikely(x)
#endif

#ifndef _lua_pushliteral_
#define _lua_pushliteral_
	#define lua_pushliteral lua_pushstring(L, "" s)
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _lua_Alloc_
#define _lua_Alloc_
	typedef void * (*lua_Alloc) (void *ud, void *ptr, size_t osize, size_t nsize);
#endif

#ifndef _UBox_
#define _UBox_
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