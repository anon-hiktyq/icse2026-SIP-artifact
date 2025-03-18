#if !defined(__LTNUM_H__)
#define __LTNUM_H__

#include "common.h"
#include LTintfloat.h
#include LTfloatint.h

#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _LUAI_NUMLT_
	#define luai_numlt ((a)<(b))
#endif

#ifndef _TTISNUMBER_
	#define ttisnumber checktype((o), LUA_TNUMBER)
#endif

#ifndef _TTISFLOAT_
	#define ttisfloat checktag((o), LUA_VNUMFLT)
#endif

#ifndef _TTISINTEGER_
	#define ttisinteger checktag((o), LUA_VNUMINT)
#endif

#ifndef _FLTVALUE_
	#define fltvalue check_exp(ttisfloat(o), val_(o).n)
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

union Value {
  struct GCObject *gc;    /* collectable objects */
  void *p;         /* light userdata */
  lua_CFunction f; /* light C functions */
  lua_Integer i;   /* integer numbers */
  lua_Number n;    /* float numbers */
  /* not used, but may avoid warnings for uninitialized value */
  lu_byte ub;
};
struct TValue {
  TValuefields;
};

void LTnumFun(void *p);

typedef struct __LTnum
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const TValue*			l;
	const TValue*			r;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} LTnum;

#endif // __LTNUM_H__