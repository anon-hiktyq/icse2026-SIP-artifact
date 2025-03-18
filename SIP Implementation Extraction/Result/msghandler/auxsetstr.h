#if !defined(__AUXSETSTR_H__)
#define __AUXSETSTR_H__

#include "common.h"
#include luaS_new.h
#include luaC_barrierback_.h
#include luaV_finishset.h

#ifndef _S2V_
	#define s2v (&(o)->val)
#endif

#ifndef _SETSVALUE2S_
	#define setsvalue2s setsvalue(L,s2v(o),s)
#endif

#ifndef _API_INCR_TOP_
	#define api_incr_top (L->top.p++, api_check(L, L->top.p <= L->ci->top.p, "stack overflow"))
#endif

#define lua_unlock ((void) 0)
#ifndef _API_CHECKPOP_
	#define api_checkpop api_check(L, (n) < L->top.p - L->ci->func.p &&  \
	                     L->tbclist.p < L->top.p - (n), \
				  "not enough free elements in the stack")
#endif

#ifndef _HOK_
	#define HOK 0
#endif

#ifndef _LUAV_FASTSET_
	#define luaV_fastset (hres = (!ttistable(t) ? HNOTATABLE : f(hvalue(t), k, val)))
#endif

#ifndef _LUAV_FINISHFASTSET_
	#define luaV_finishfastset luaC_barrierback(L, gcvalue(t), v)
#endif

struct lua_State;
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
typedef StackValue *StkId;
union {
  StkId p;  /* actual pointer */
  ptrdiff_t offset;  /* used while the stack is being reallocated */
};
struct GCObject {
  CommonHeader;
};
struct TString {
  CommonHeader;
  lu_byte extra;  /* reserved words for short strings; "has hash" for longs */
  ls_byte shrlen;  /* length for short strings, negative for long strings */
  unsigned int hash;
  union {
    size_t lnglen;  /* length for long strings */
    struct TString *hnext;  /* linked list for hash table */
  } u;
  char *contents;  /* pointer to content in long strings */
  lua_Alloc falloc;  /* deallocation function for external strings */
  void *ud;  /* user data for external strings */
};
struct Table {
  CommonHeader;
  lu_byte flags;  /* 1<<p means tagmethod(p) is not present */
  lu_byte lsizenode;  /* log2 of number of slots of 'node' array */
  unsigned int asize;  /* number of slots in 'array' array */
  Value *array;  /* array part */
  Node *node;
  struct Table *metatable;
  GCObject *gclist;
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

void auxsetstrFun(void *p);

typedef struct __auxsetstr
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	const TValue*			t;
	const char*			k;
	/* Statement Variables*/
	/* Argument Variables */
} auxsetstr;

#endif // __AUXSETSTR_H__