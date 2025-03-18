#if !defined(__L_STR2D_H__)
#define __L_STR2D_H__

#include "common.h"
#include "l_str2dloc.h"

#ifndef _LUA_GETLOCALEDECPOINT_
	#define lua_getlocaledecpoint (localeconv()->decimal_point[0])
#endif

#ifndef _CAST_UCHAR_
	#define cast_uchar cast(unsigned char, (i))
#endif

#ifndef _LTOLOWER_
	#define ltolower (tolower(c))
#endif

#ifndef _L_MAXLENNUM_
	#define L_MAXLENNUM 200
#endif

#ifndef _LUA_NUMBER_
	typedef LUA_NUMBER lua_Number;
#endif


void l_str2dFun(void *p);

typedef struct __l_str2d
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	const char *			ret;
	/* In&Output Variables */
	const char*			s;
	lua_Number*			result;
	/* Statement Variables*/
	/* Argument Variables */
} l_str2d;

#endif // __L_STR2D_H__