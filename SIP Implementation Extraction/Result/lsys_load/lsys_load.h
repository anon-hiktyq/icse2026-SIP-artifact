#if !defined(__LSYS_LOAD_H__)
#define __LSYS_LOAD_H__

#include "common.h"


#ifndef _lua_pushliteral_
#define _lua_pushliteral_
	#define lua_pushliteral lua_pushstring(L, "" s)
#endif

#ifndef _DLMSG_
#define _DLMSG_
	#define DLMSG "dynamic libraries not enabled; check your Lua installation"
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif


void lsys_loadFun(void *p);

typedef struct __lsys_load
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			seeglb;
	/* Output Variables */
	void *			ret;
	/* In&Output Variables */
	lua_State*			L;
	const char*			path;
	/* Statement Variables*/
	/* Argument Variables */
} lsys_load;

#endif // __LSYS_LOAD_H__