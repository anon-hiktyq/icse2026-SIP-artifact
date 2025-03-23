#if !defined(__L_STR2DLOC_H__)
#define __L_STR2DLOC_H__

#include "common.h"


#ifndef _lua_str2number_
#define _lua_str2number_
	#define lua_str2number ((lua_Number)strtod((s), (p)))
#endif

#ifndef _lua_strx2number_
#define _lua_strx2number_
	#define lua_strx2number lua_str2number(s,p)
#endif

#ifndef _cast_uchar_
#define _cast_uchar_
	#define cast_uchar cast(unsigned char, (i))
#endif

#ifndef _lisspace_
#define _lisspace_
	#define lisspace (isspace(c))
#endif

#ifndef _lua_Number_
#define _lua_Number_
	typedef LUA_NUMBER lua_Number;
#endif

#ifndef _lu_byte_
#define _lu_byte_
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