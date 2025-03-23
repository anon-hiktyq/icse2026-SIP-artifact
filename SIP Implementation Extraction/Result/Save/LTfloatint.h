#if !defined(__LTFLOATINT_H__)
#define __LTFLOATINT_H__

#include "common.h"
#include "luaV_flttointeger.h"

#ifndef _cast_num_
#define _cast_num_
	#define cast_num cast(lua_Number, (i))
#endif

#ifndef _luai_numlt_
#define _luai_numlt_
	#define luai_numlt ((a)<(b))
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


void LTfloatintFun(void *p);

typedef struct __LTfloatint
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	lua_Number			f;
	lua_Integer			i;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} LTfloatint;

#endif // __LTFLOATINT_H__