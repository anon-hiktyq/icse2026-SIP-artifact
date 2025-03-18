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
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	lua_Number			n;
	/* 输出端口 */
	unsigned int*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} l_hashfloat;

#endif // __L_HASHFLOAT_H__