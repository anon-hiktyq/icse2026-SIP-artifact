#if !defined(__LUA_NEXT_H__)
#define __LUA_NEXT_H__

#include "common.h"
#include "gettable.h"
#include "luaH_next.h"

#ifndef _api_incr_top_
#define _api_incr_top_
	#define api_incr_top (L->top.p++, api_check(L, L->top.p <= L->ci->top.p, "stack overflow"))
#endif

#ifndef _lua_lock_
#define _lua_lock_
	#define lua_lock ((void) 0)
#endif

#ifndef _lua_unlock_
#define _lua_unlock_
	#define lua_unlock ((void) 0)
#endif

#ifndef _api_checkpop_
#define _api_checkpop_
	#define api_checkpop api_check(L, (n) < L->top.p - L->ci->func.p &&  \
	                     L->tbclist.p < L->top.p - (n), \
				  "not enough free elements in the stack")
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _StkId_
#define _StkId_
	typedef StackValue *StkId;
#endif

#ifndef _StkIdRel_
#define _StkIdRel_
	union {
	  StkId p;  /* actual pointer */
	  ptrdiff_t offset;  /* used while the stack is being reallocated */
	};
#endif

#ifndef _Table_
#define _Table_
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
#endif

#ifndef _lua_State_
#define _lua_State_
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


void lua_nextFun(void *p);

typedef struct __lua_next
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			idx;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	lua_State*			L;
	/* Statement Variables*/
	/* Argument Variables */
} lua_next;

#endif // __LUA_NEXT_H__