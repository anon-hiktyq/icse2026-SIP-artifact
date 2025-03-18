#if !defined(__TOSTRINGBUFFFLOAT_H__)
#define __TOSTRINGBUFFFLOAT_H__

#include "common.h"


#ifndef _LUA_NUMBER_FMT_
	#define LUA_NUMBER_FMT "%.15g"
#endif

#ifndef _LUA_NUMBER_FMT_N_
	#define LUA_NUMBER_FMT_N "%.17g"
#endif

#ifndef _LUA_STR2NUMBER_
	#define lua_str2number ((lua_Number)strtod((s), (p)))
#endif

#ifndef _L_SPRINTF_
	#define l_sprintf ((void)(sz), sprintf(s,f,i))
#endif

#ifndef _LUA_GETLOCALEDECPOINT_
	#define lua_getlocaledecpoint (localeconv()->decimal_point[0])
#endif

#ifndef _LUA_N2SBUFFSZ_
	#define LUA_N2SBUFFSZ 64
#endif

#ifndef _LUA_NUMBER_
	typedef LUA_NUMBER lua_Number;
#endif


void tostringbuffFloatFun(void *p);

typedef struct __tostringbuffFloat
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	lua_Number			n;
	/* Output Variables */
	int			len;
	int*			ret;
	/* In&Output Variables */
	char*			buff;
	/* Statement Variables*/
	/* Argument Variables */
} tostringbuffFloat;

#endif // __TOSTRINGBUFFFLOAT_H__