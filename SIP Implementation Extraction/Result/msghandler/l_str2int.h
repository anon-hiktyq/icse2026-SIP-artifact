#if !defined(__L_STR2INT_H__)
#define __L_STR2INT_H__

#include "common.h"
#include isneg.h
#include luaO_hexavalue.h

#ifndef _CAST_UINT_
	#define cast_uint cast(unsigned int, (i))
#endif

#ifndef _CAST_UCHAR_
	#define cast_uchar cast(unsigned char, (i))
#endif

#ifndef _L_CASTU2S_
	#define l_castU2S ((lua_Integer)(i))
#endif

#ifndef _LISDIGIT_
	#define lisdigit (isdigit(c))
#endif

#ifndef _LISSPACE_
	#define lisspace (isspace(c))
#endif

#ifndef _LISXDIGIT_
	#define lisxdigit (isxdigit(c))
#endif

#ifndef _MAXBY10_
	#define MAXBY10 cast(lua_Unsigned, LUA_MAXINTEGER / 10)
#endif

#ifndef _MAXLASTD_
	#define MAXLASTD cast_int(LUA_MAXINTEGER % 10)
#endif

#ifndef _LUA_INTEGER_
	typedef LUA_INTEGER lua_Integer;
#endif

#ifndef _LUA_UNSIGNED_
	typedef LUA_UNSIGNED lua_Unsigned;
#endif

#ifndef _LU_BYTE_
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