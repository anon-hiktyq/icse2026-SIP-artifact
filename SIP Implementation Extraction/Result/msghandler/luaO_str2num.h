#if !defined(__LUAO_STR2NUM_H__)
#define __LUAO_STR2NUM_H__

#include "common.h"
#include "l_str2int.h"
#include "l_str2d.h"

#ifndef _ct_diff2sz_
#define _ct_diff2sz_
	#define ct_diff2sz ((size_t)(df))
#endif

#ifndef _setfltvalue_
#define _setfltvalue_
	#define setfltvalue { TValue *io=(obj); val_(io).n=(x); settt_(io, LUA_VNUMFLT); }
#endif

#ifndef _setivalue_
#define _setivalue_
	#define setivalue { TValue *io=(obj); val_(io).i=(x); settt_(io, LUA_VNUMINT); }
#endif

#ifndef _lua_Number_
#define _lua_Number_
	typedef LUA_NUMBER lua_Number;
#endif

#ifndef _lua_Integer_
#define _lua_Integer_
	typedef LUA_INTEGER lua_Integer;
#endif

#ifndef _lu_byte_
#define _lu_byte_
	typedef unsigned char lu_byte;
#endif

#ifndef _Value_
#define _Value_
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

#ifndef _TValue_
#define _TValue_
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