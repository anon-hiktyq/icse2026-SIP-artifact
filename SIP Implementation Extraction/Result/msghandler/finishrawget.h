#if !defined(__FINISHRAWGET_H__)
#define __FINISHRAWGET_H__

#include "common.h"


#ifndef _NOVARIANT_
	#define novariant ((t) & 0x0F)
#endif

#ifndef _S2V_
	#define s2v (&(o)->val)
#endif

#ifndef _TAGISEMPTY_
	#define tagisempty (novariant(tag) == LUA_TNIL)
#endif

#ifndef _SETNILVALUE_
	#define setnilvalue settt_(obj, LUA_VNIL)
#endif

#ifndef _API_INCR_TOP_
	#define api_incr_top (L->top.p++, api_check(L, L->top.p <= L->ci->top.p, "stack overflow"))
#endif

#define lua_unlock ((void) 0)
struct lua_State;
#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif

struct TValue {
  TValuefields;
};
typedef StackValue *StkId;
union {
  StkId p;  /* actual pointer */
  ptrdiff_t offset;  /* used while the stack is being reallocated */
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

void finishrawgetFun(void *p);

typedef struct __finishrawget
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	lu_byte			tag;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	lua_State*			L;
	/* Statement Variables*/
	/* Argument Variables */
} finishrawget;

#endif // __FINISHRAWGET_H__