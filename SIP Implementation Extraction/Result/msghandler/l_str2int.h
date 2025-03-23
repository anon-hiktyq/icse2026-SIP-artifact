#if !defined(__L_STR2INT_H__)
#define __L_STR2INT_H__

#include "common.h"
#include "isneg.h"
#include "luaO_hexavalue.h"

#ifndef _cast_uint_
#define _cast_uint_
	#define cast_uint cast(unsigned int, (i))
#endif

#ifndef _cast_uchar_
#define _cast_uchar_
	#define cast_uchar cast(unsigned char, (i))
#endif

#ifndef _l_castU2S_
#define _l_castU2S_
	#define l_castU2S ((lua_Integer)(i))
#endif

#ifndef _lisdigit_
#define _lisdigit_
	#define lisdigit (isdigit(c))
#endif

#ifndef _lisspace_
#define _lisspace_
	#define lisspace (isspace(c))
#endif

#ifndef _lisxdigit_
#define _lisxdigit_
	#define lisxdigit (isxdigit(c))
#endif

#ifndef _MAXBY10_
#define _MAXBY10_
	#define MAXBY10 cast(lua_Unsigned, LUA_MAXINTEGER / 10)
#endif

#ifndef _MAXLASTD_
#define _MAXLASTD_
	#define MAXLASTD cast_int(LUA_MAXINTEGER % 10)
#endif

#ifndef _lua_Integer_
#define _lua_Integer_
	typedef LUA_INTEGER lua_Integer;
#endif

#ifndef _lua_Unsigned_
#define _lua_Unsigned_
	typedef LUA_UNSIGNED lua_Unsigned;
#endif

#ifndef _lu_byte_
#define _lu_byte_
	typedef unsigned char lu_byte;
#endif


void l_str2intFun(void *p);

typedef struct __l_str2int
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const char*			s;
	/* Output Variables */
	const char *			ret;
	/* In&Output Variables */
	lua_Integer*			result;
	/* Statement Variables*/
	/* Argument Variables */
} l_str2int;

#endif // __L_STR2INT_H__