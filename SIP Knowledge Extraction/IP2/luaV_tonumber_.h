#if !defined(__LUAV_TONUMBER__H__)
#define __LUAV_TONUMBER__H__

#include "common.h"
#include l_strton.h

#ifndef _CAST_NUM_
	#define cast_num cast(lua_Number, (i))
#endif

#ifndef _TTISINTEGER_
	#define ttisinteger checktag((o), LUA_VNUMINT)
#endif

#ifndef _NVALUE_
	#define nvalue check_exp(ttisnumber(o), \
		(ttisinteger(o) ? cast_num(ivalue(o)) : fltvalue(o)))
#endif

#ifndef _IVALUE_
	#define ivalue check_exp(ttisinteger(o), val_(o).i)
#endif

#ifndef _LUA_NUMBER_
	typedef LUA_NUMBER lua_Number;
#endif

#ifndef _LUA_INTEGER_
	typedef LUA_INTEGER lua_Integer;
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif

#ifndef _VALUE_
	union Value {
	  struct GCObject *gc;    /* collectable objects */
	  void *p;         /* light userdata */
	  lua_CFunction f; /* light C functions */
	  lua_Integer i;   /* integer numbers */
	  lua_Number n;    /* float numbers */
	  /* not used, but may avoid warnings for uninitialized value */
	  lu_byte ub;
	};
#endif

#ifndef _TVALUE_
	struct TValue {
	  TValuefields;
	};
#endif


void luaV_tonumber_Fun(void *p);

typedef struct __luaV_tonumber_
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	/* 输出端口 */
	int*			ret;
	/* 输入输出端口 */
	const TValue*			obj;
	lua_Number*			n;
	/* 状态变量 */
	/* 参数变量 */
} luaV_tonumber_;

#endif // __LUAV_TONUMBER__H__