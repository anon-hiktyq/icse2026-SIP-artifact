#if !defined(__LUAF_CLOSE_H__)
#define __LUAF_CLOSE_H__

#include "common.h"
#include "luaF_closeupval.h"
#include "poptbclist.h"
#include "prepcallclosemth.h"

#ifndef _SAVESTACK_
	#define savestack (cast_charp(pt) - cast_charp(L->stack.p))
#endif

#ifndef _RESTORESTACK_
	#define restorestack cast(StkId, cast_charp(L->stack.p) + (n))
#endif

struct lua_State;
#ifndef _TSTATUS_
	typedef lu_byte TStatus;
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

#ifndef _LUA_STATE_
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
#endif


void luaF_closeFun(void *p);

typedef struct __luaF_close
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	TStatus			status;
	int			yy;
	/* Output Variables */
	StkId*			ret;
	/* In&Output Variables */
	lua_State*			L;
	StkId			level;
	/* Statement Variables*/
	/* Argument Variables */
} luaF_close;

#endif // __LUAF_CLOSE_H__