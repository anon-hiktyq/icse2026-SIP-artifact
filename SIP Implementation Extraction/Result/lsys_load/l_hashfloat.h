#if !defined(__L_HASHFLOAT_H__)
#define __L_HASHFLOAT_H__

#include "common.h"


#ifndef _LUA_NUMBERTOINTEGER_
	#define lua_numbertointeger ((n) >= (LUA_NUMBER)(LUA_MININTEGER) && \
	   (n) < -(LUA_NUMBER)(LUA_MININTEGER) && \
	      (*(p) = (LUA_INTEGER)(n), 1))
#endif

#ifndef _L_MATHOP_
	#define l_mathop (lua_Number)op
#endif

#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _CAST_NUM_
	#define cast_num cast(lua_Number, (i))
#endif

#ifndef _CAST_UINT_
	#define cast_uint cast(unsigned int, (i))
#endif

#ifndef _LUAI_NUMISNAN_
	#define luai_numisnan (!luai_numeq((a), (a)))
#endif

#ifndef _LUA_NUMBER_
	typedef LUA_NUMBER lua_Number;
#endif

#ifndef _LUA_INTEGER_
	typedef LUA_INTEGER lua_Integer;
#endif


void l_hashfloatFun(void *p);

typedef struct __l_hashfloat
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	lua_Number			n;
	/* Output Variables */
	unsigned int*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} l_hashfloat;

#endif // __L_HASHFLOAT_H__