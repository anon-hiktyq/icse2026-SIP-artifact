#if !defined(__FLOATFORLOOP_H__)
#define __FLOATFORLOOP_H__

#include "common.h"


#ifndef _luai_numadd_
#define _luai_numadd_
	#define luai_numadd ((a)+(b))
#endif

#ifndef _luai_numlt_
#define _luai_numlt_
	#define luai_numlt ((a)<(b))
#endif

#ifndef _luai_numle_
#define _luai_numle_
	#define luai_numle ((a)<=(b))
#endif

#ifndef _s2v_
#define _s2v_
	#define s2v (&(o)->val)
#endif

#ifndef _fltvalue_
#define _fltvalue_
	#define fltvalue check_exp(ttisfloat(o), val_(o).n)
#endif

#ifndef _chgfltvalue_
#define _chgfltvalue_
	#define chgfltvalue { TValue *io=(obj); lua_assert(ttisfloat(io)); val_(io).n=(x); }
#endif

#ifndef _lua_Number_
#define _lua_Number_
	typedef LUA_NUMBER lua_Number;
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

#ifndef _StkId_
#define _StkId_
	typedef StackValue *StkId;
#endif


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