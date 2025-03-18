#if !defined(__FLOATFORLOOP_H__)
#define __FLOATFORLOOP_H__

#include "common.h"


#ifndef _LUAI_NUMADD_
	#define luai_numadd ((a)+(b))
#endif

#ifndef _LUAI_NUMLT_
	#define luai_numlt ((a)<(b))
#endif

#ifndef _LUAI_NUMLE_
	#define luai_numle ((a)<=(b))
#endif

#ifndef _S2V_
	#define s2v (&(o)->val)
#endif

#ifndef _FLTVALUE_
	#define fltvalue check_exp(ttisfloat(o), val_(o).n)
#endif

#ifndef _CHGFLTVALUE_
	#define chgfltvalue { TValue *io=(obj); lua_assert(ttisfloat(io)); val_(io).n=(x); }
#endif

#ifndef _LUA_NUMBER_
	typedef LUA_NUMBER lua_Number;
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
typedef StackValue *StkId;

void floatforloopFun(void *p);

typedef struct __floatforloop
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	StkId			ra;
	/* Statement Variables*/
	/* Argument Variables */
} floatforloop;

#endif // __FLOATFORLOOP_H__