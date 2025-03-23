#if !defined(__LEINTFLOAT_H__)
#define __LEINTFLOAT_H__

#include "common.h"
#include "luaV_flttointeger.h"

#ifndef _cast_num_
#define _cast_num_
	#define cast_num cast(lua_Number, (i))
#endif

#ifndef _luai_numle_
#define _luai_numle_
	#define luai_numle ((a)<=(b))
#endif

#ifndef _l_intfitsf_
#define _l_intfitsf_
	#define l_intfitsf 1
#endif

#ifndef _lua_Number_
#define _lua_Number_
	typedef LUA_NUMBER lua_Number;
#endif

#ifndef _lua_Integer_
#define _lua_Integer_
	typedef LUA_INTEGER lua_Integer;
#endif

#ifndef _F2Imod_
#define _F2Imod_
	enum {
	  F2Ieq,     /* no rounding; accepts only integral values */
	  F2Ifloor,  /* takes the floor of the number */
	  F2Iceil    /* takes the ceiling of the number */
	};
#endif


void LEintfloatFun(void *p);

typedef struct __LEintfloat
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	lua_Integer			i;
	lua_Number			f;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} LEintfloat;

#endif // __LEINTFLOAT_H__