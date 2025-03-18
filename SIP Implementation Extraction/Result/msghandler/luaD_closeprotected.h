#if !defined(__LUAD_CLOSEPROTECTED_H__)
#define __LUAD_CLOSEPROTECTED_H__

#include "common.h"
#include luaD_rawrunprotected.h

#ifndef _L_LIKELY_
	#define l_likely luai_likely(x)
#endif

#ifndef _LUA_OK_
	#define LUA_OK 0
#endif

#ifndef _RESTORESTACK_
	#define restorestack cast(StkId, cast_charp(L->stack.p) + (n))
#endif

struct lua_State;
#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif

#ifndef _TSTATUS_
	typedef lu_byte TStatus;
#endif

#ifndef _CALLINFO_
	typedef struct CallInfo CallInfo;
#endif

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
#ifndef _CLOSEP_
	struct CloseP {
	  StkId level;
	  TStatus status;
	};
#endif


void luaD_closeprotectedFun(void *p);

typedef struct __luaD_closeprotected
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	ptrdiff_t			level;
	TStatus			status;
	/* Output Variables */
	TStatus*			ret;
	/* In&Output Variables */
	lua_State*			L;
	/* Statement Variables*/
	/* Argument Variables */
} luaD_closeprotected;

#endif // __LUAD_CLOSEPROTECTED_H__