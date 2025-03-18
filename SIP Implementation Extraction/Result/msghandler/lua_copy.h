#if !defined(__LUA_COPY_H__)
#define __LUA_COPY_H__

#include "common.h"
#include index2value.h
#include index2value.h

#ifndef _SETOBJ_
	#define setobj { TValue *io1=(obj1); const TValue *io2=(obj2); \
	          io1->value_ = io2->value_; settt_(io1, io2->tt_); \
		  checkliveness(L,io1); lua_assert(!isnonstrictnil(io1)); }
#endif

#ifndef _S2V_
	#define s2v (&(o)->val)
#endif

#ifndef _CLCVALUE_
	#define clCvalue check_exp(ttisCclosure(o), gco2ccl(val_(o).gc))
#endif

#define api_check ((void)(l), lua_assert((e) && msg))
#define lua_lock ((void) 0)
#define lua_unlock ((void) 0)
#ifndef _LUAC_BARRIER_
	#define luaC_barrier (  \
		iscollectable(v) ? luaC_objbarrier(L,p,gcvalue(v)) : cast_void(0))
#endif

#ifndef _ISVALID_
	#define isvalid ((o) != &G(L)->nilvalue)
#endif

#ifndef _ISUPVALUE_
	#define isupvalue ((i) < LUA_REGISTRYINDEX)
#endif

struct lua_State;
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
#ifndef _CCLOSURE_
	struct CClosure {
	  ClosureHeader;
	  lua_CFunction f;
	  TValue upvalue[1];  /* list of upvalues */
	};
#endif

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

void lua_copyFun(void *p);

typedef struct __lua_copy
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			fromidx;
	int			toidx;
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	/* Statement Variables*/
	/* Argument Variables */
} lua_copy;

#endif // __LUA_COPY_H__