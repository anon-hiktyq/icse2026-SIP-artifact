#if !defined(__NEWBOX_H__)
#define __NEWBOX_H__

#include "common.h"
#include lua_newuserdatauv.h
#include luaL_newmetatable.h
#include luaL_setfuncs.h
#include lua_setmetatable.h

struct lua_State;
#ifndef _LUAL_REG_
	struct luaL_Reg {
	  const char *name;
	  lua_CFunction func;
	};
#endif

#ifndef _UBOX_
	struct UBox {
	  void *box;
	  size_t bsize;
	};
#endif


void newboxFun(void *p);

typedef struct __newbox
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	/* Statement Variables*/
	/* Argument Variables */
} newbox;

#endif // __NEWBOX_H__