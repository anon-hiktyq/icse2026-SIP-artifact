#if !defined(__FREEUPVAL_H__)
#define __FREEUPVAL_H__

#include "common.h"
#include "luaF_unlinkupval.h"

#ifndef _luaM_free_
#define _luaM_free_
	#define luaM_free luaM_free_(L, (b), sizeof(*(b)))
#endif

#ifndef _upisopen_
#define _upisopen_
	#define upisopen ((up)->v.p != &(up)->u.value)
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _TValue_
#define _TValue_
	struct TValue {
	  TValuefields;
	};
#endif

#ifndef _UpVal_
#define _UpVal_
	struct UpVal {
	  CommonHeader;
	  union {
	    TValue *p;  /* points to stack or to its own value */
	    ptrdiff_t offset;  /* used while the stack is being reallocated */
	  } v;
	  union {
	    struct {  /* (when open) */
	      struct UpVal *next;  /* linked list */
	      struct UpVal **previous;
	    } open;
	    TValue value;  /* the value (when closed) */
	  } u;
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


void freeupvalFun(void *p);

typedef struct __freeupval
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	UpVal*			uv;
	/* Statement Variables*/
	/* Argument Variables */
} freeupval;

#endif // __FREEUPVAL_H__