#if !defined(__SWEEPTOLIVE_H__)
#define __SWEEPTOLIVE_H__

#include "common.h"
#include sweeplist.h

struct lua_State;
#ifndef _L_MEM_
	typedef ptrdiff_t l_mem;
#endif

struct GCObject {
  CommonHeader;
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

void sweeptoliveFun(void *p);

typedef struct __sweeptolive
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	GCObject **			ret;
	/* In&Output Variables */
	lua_State*			L;
	GCObject**			p;
	/* Statement Variables*/
	/* Argument Variables */
} sweeptolive;

#endif // __SWEEPTOLIVE_H__