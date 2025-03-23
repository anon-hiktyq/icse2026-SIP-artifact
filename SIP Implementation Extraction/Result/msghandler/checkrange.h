#if !defined(__CHECKRANGE_H__)
#define __CHECKRANGE_H__

#include "common.h"


#ifndef _cast_uint_
#define _cast_uint_
	#define cast_uint cast(unsigned int, (i))
#endif

#ifndef _l_castS2U_
#define _l_castS2U_
	#define l_castS2U ((lua_Unsigned)(i))
#endif

#ifndef _lua_Integer_
#define _lua_Integer_
	typedef LUA_INTEGER lua_Integer;
#endif


void checkrangeFun(void *p);

typedef struct __checkrange
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	lua_Integer			k;
	unsigned int			limit;
	/* Output Variables */
	unsigned int*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} checkrange;

#endif // __CHECKRANGE_H__