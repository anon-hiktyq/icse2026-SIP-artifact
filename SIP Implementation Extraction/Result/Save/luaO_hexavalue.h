#if !defined(__LUAO_HEXAVALUE_H__)
#define __LUAO_HEXAVALUE_H__

#include "common.h"


#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _CAST_BYTE_
	#define cast_byte cast(lu_byte, (i))
#endif

#ifndef _LISDIGIT_
	#define lisdigit (isdigit(c))
#endif

#ifndef _LISXDIGIT_
	#define lisxdigit (isxdigit(c))
#endif

#ifndef _LTOLOWER_
	#define ltolower (tolower(c))
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif


void luaO_hexavalueFun(void *p);

typedef struct __luaO_hexavalue
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			c;
	/* Output Variables */
	lu_byte*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} luaO_hexavalue;

#endif // __LUAO_HEXAVALUE_H__