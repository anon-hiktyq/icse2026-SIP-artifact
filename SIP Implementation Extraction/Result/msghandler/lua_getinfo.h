#if !defined(__LUA_GETINFO_H__)
#define __LUA_GETINFO_H__

#include "common.h"
#include auxgetinfo.h
#include collectvalidlines.h

#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _SETOBJ2S_
	#define setobj2s setobj(L,s2v(o1),o2)
#endif

#ifndef _S2V_
	#define s2v (&(o)->val)
#endif

#ifndef _TTISFUNCTION_
	#define ttisfunction checktype(o, LUA_TFUNCTION)
#endif

#ifndef _TTISCLOSURE_
	#define ttisclosure (ttisLclosure(o) || ttisCclosure(o))
#endif

#ifndef _CLVALUE_
	#define clvalue check_exp(ttisclosure(o), gco2cl(val_(o).gc))
#endif

#define api_check ((void)(l), lua_assert((e) && msg))
#ifndef _API_INCR_TOP_
	#define api_incr_top (L->top.p++, api_check(L, L->top.p <= L->ci->top.p, "stack overflow"))
#endif

#define lua_lock ((void) 0)
#define lua_unlock ((void) 0)
struct lua_State;
#ifndef _LUA_DEBUG_
	struct lua_Debug;
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif

#ifndef _CALLINFO_
	typedef struct CallInfo CallInfo;
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
union {
  StkId p;  /* actual pointer */
  ptrdiff_t offset;  /* used while the stack is being reallocated */
};
struct GCObject {
  CommonHeader;
};
union Closure {
  CClosure c;
  LClosure l;
};
struct lua_State {
  CommonHeader;
  lu_byte allowhook;
  TStatus status;
  StkIdRel top;  /* first free slot in the stack */
  struct global_State *l_G;
  CallInfo *ci;  /* call info for current function */
  StkIdRel stack_last;  /* end of stack (last element + 1) */
  StkIdRel stack;  /* stack base */
  UpVal *openupval;  /* list of open upvalues in this stack */
  StkIdRel tbclist;  /* list of to-be-closed variables */
  GCObject *gclist;
  struct lua_State *twups;  /* list of threads with open upvalues */
  struct lua_longjmp *errorJmp;  /* current error recover point */
  CallInfo base_ci;  /* CallInfo for first level (C host) */
  volatile lua_Hook hook;
  ptrdiff_t errfunc;  /* current error handling function (stack index) */
  l_uint32 nCcalls;  /* number of nested non-yieldable or C calls */
  int oldpc;  /* last pc traced */
  int nci;  /* number of items in 'ci' list */
  int basehookcount;
  int hookcount;
  volatile l_signalT hookmask;
  struct {  /* info about transferred values (for call/return hooks) */
    int ftransfer;  /* offset of first value transferred */
    int ntransfer;  /* number of values transferred */
  } transferinfo;
};

void lua_getinfoFun(void *p);

typedef struct __lua_getinfo
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	int			status;
	int*			ret;
	/* In&Output Variables */
	lua_State*			L;
	const char*			what;
	lua_Debug*			ar;
	/* Statement Variables*/
	/* Argument Variables */
} lua_getinfo;

#endif // __LUA_GETINFO_H__