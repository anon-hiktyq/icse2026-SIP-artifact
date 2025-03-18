#if !defined(__L_STR2DLOC_H__)
#define __L_STR2DLOC_H__

#include "common.h"


#ifndef _LUA_STR2NUMBER_
	#define lua_str2number ((lua_Number)strtod((s), (p)))
#endif

#ifndef _LUA_STRX2NUMBER_
	#define lua_strx2number lua_str2number(s,p)
#endif

#ifndef _CAST_UCHAR_
	#define cast_uchar cast(unsigned char, (i))
#endif

#ifndef _LISSPACE_
	#define lisspace (isspace(c))
#endif

#ifndef _LUA_NUMBER_
	typedef LUA_NUMBER lua_Number;
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif


void l_str2dlocFun(void *p);

typedef struct __l_str2dloc
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const char*			s;
	int			mode;
	/* Output Variables */
	const char *			ret;
	/* In&Output Variables */
	lua_Number*			result;
	/* Statement Variables*/
	/* Argument Variables */
} l_str2dloc;

#endif // __L_STR2DLOC_H__