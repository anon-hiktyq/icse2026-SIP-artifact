#if !defined(__GETCURRENTLINE_H__)
#define __GETCURRENTLINE_H__

#include "common.h"
#include "luaG_getfuncline.h"

#ifndef _CI_FUNC_
	#define ci_func (clLvalue(s2v((ci)->func.p)))
#endif

#ifndef _CALLINFO_
	typedef struct CallInfo CallInfo;
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

#ifndef _STKID_
	typedef StackValue *StkId;
#endif

#ifndef _STKIDREL_
	union {
	  StkId p;  /* actual pointer */
	  ptrdiff_t offset;  /* used while the stack is being reallocated */
	};
#endif

#ifndef _GCOBJECT_
	struct GCObject {
	  CommonHeader;
	};
#endif

#ifndef _LCLOSURE_
	struct LClosure {
	  ClosureHeader;
	  struct Proto *p;
	  UpVal *upvals[1];  /* list of upvalues */
	};
#endif

#ifndef _CLOSURE_
	union Closure {
	  CClosure c;
	  LClosure l;
	};
#endif


void getcurrentlineFun(void *p);

typedef struct __getcurrentline
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	CallInfo*			ci;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} getcurrentline;

#endif // __GETCURRENTLINE_H__