#if !defined(__LUAO_STR2NUM_H__)
#define __LUAO_STR2NUM_H__

#include "common.h"
#include "l_str2int.h"
#include "l_str2d.h"

#ifndef _CT_DIFF2SZ_
	#define ct_diff2sz ((size_t)(df))
#endif

#ifndef _SETFLTVALUE_
	#define setfltvalue { TValue *io=(obj); val_(io).n=(x); settt_(io, LUA_VNUMFLT); }
#endif

#ifndef _SETIVALUE_
	#define setivalue { TValue *io=(obj); val_(io).i=(x); settt_(io, LUA_VNUMINT); }
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


void luaO_str2numFun(void *p);

typedef struct __luaO_str2num
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	size_t*			ret;
	/* In&Output Variables */
	const char*			s;
	TValue*			o;
	/* Statement Variables*/
	/* Argument Variables */
} luaO_str2num;

#endif // __LUAO_STR2NUM_H__