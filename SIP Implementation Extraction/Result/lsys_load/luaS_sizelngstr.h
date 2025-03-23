#if !defined(__LUAS_SIZELNGSTR_H__)
#define __LUAS_SIZELNGSTR_H__

#include "common.h"


#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
#endif

#ifndef _LSTRREG_
#define _LSTRREG_
	#define LSTRREG -1
#endif

#ifndef _LSTRFIX_
#define _LSTRFIX_
	#define LSTRFIX -2
#endif

#ifndef _LSTRMEM_
#define _LSTRMEM_
	#define LSTRMEM -3
#endif


void luaS_sizelngstrFun(void *p);

typedef struct __luaS_sizelngstr
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	size_t			len;
	int			kind;
	/* Output Variables */
	size_t*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} luaS_sizelngstr;

#endif // __LUAS_SIZELNGSTR_H__