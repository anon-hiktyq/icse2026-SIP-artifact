#if !defined(__LUAO_HEXAVALUE_H__)
#define __LUAO_HEXAVALUE_H__

#include "common.h"


#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
#endif

#ifndef _cast_byte_
#define _cast_byte_
	#define cast_byte cast(lu_byte, (i))
#endif

#ifndef _lisdigit_
#define _lisdigit_
	#define lisdigit (isdigit(c))
#endif

#ifndef _lisxdigit_
#define _lisxdigit_
	#define lisxdigit (isxdigit(c))
#endif

#ifndef _ltolower_
#define _ltolower_
	#define ltolower (tolower(c))
#endif

#ifndef _lu_byte_
#define _lu_byte_
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