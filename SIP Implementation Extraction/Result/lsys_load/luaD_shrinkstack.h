#if !defined(__LUAD_SHRINKSTACK_H__)
#define __LUAD_SHRINKSTACK_H__

#include "common.h"
#include "stackinuse.h"
#include "luaD_reallocstack.h"
#include "luaE_shrinkCI.h"

#ifndef _STACKSIZE_
	#define stacksize cast_int((th)->stack_last.p - (th)->stack.p)
#endif

#ifndef _CONDMOVESTACK_
	#define condmovestack { int sz_ = stacksize(L); pre; luaD_reallocstack((L), sz_, 0); pos; }
#endif

#ifndef _MAXSTACK_
	#define MAXSTACK cast_int(LUAI_MAXSTACK < MAXSTACK_BYSIZET  \
				        ? LUAI_MAXSTACK : MAXSTACK_BYSIZET)
#endif

struct lua_State;
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


void luaD_shrinkstackFun(void *p);

typedef struct __luaD_shrinkstack
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	/* Statement Variables*/
	/* Argument Variables */
} luaD_shrinkstack;

#endif // __LUAD_SHRINKSTACK_H__