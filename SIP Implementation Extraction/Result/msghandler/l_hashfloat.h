#if !defined(__L_HASHFLOAT_H__)
#define __L_HASHFLOAT_H__

#include "common.h"


#ifndef _lua_numbertointeger_
#define _lua_numbertointeger_
	#define lua_numbertointeger ((n) >= (LUA_NUMBER)(LUA_MININTEGER) && \
	   (n) < -(LUA_NUMBER)(LUA_MININTEGER) && \
	      (*(p) = (LUA_INTEGER)(n), 1))
#endif

#ifndef _l_mathop_
#define _l_mathop_
	#define l_mathop (lua_Number)op
#endif

#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
#endif

#ifndef _cast_num_
#define _cast_num_
	#define cast_num cast(lua_Number, (i))
#endif

#ifndef _cast_uint_
#define _cast_uint_
	#define cast_uint cast(unsigned int, (i))
#endif

#ifndef _luai_numisnan_
#define _luai_numisnan_
	#define luai_numisnan (!luai_numeq((a), (a)))
#endif

#ifndef _lua_Number_
#define _lua_Number_
	typedef LUA_NUMBER lua_Number;
#endif

#ifndef _lua_Integer_
#define _lua_Integer_
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