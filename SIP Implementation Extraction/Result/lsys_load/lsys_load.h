#if !defined(__LSYS_LOAD_H__)
#define __LSYS_LOAD_H__

#include "common.h"


#define lua_pushliteral lua_pushstring(L, "" s)
#define DLMSG "dynamic libraries not enabled; check your Lua installation"

void lsys_loadFun(void *p);

typedef struct __lsys_load
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			seeglb;
	/* Output Variables */
	Unknown type*			lib;
	void *			ret;
	/* In&Output Variables */
	lua_State*			L;
	const char*			path;
	/* Statement Variables*/
	/* Argument Variables */
} lsys_load;

#endif // __LSYS_LOAD_H__