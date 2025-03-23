#if !defined(__LUAF_FINDUPVAL_H__)
#define __LUAF_FINDUPVAL_H__

#include "common.h"
#include "newupval.h"

#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
#endif

#ifndef _G_
#define _G_
	#define G (L->l_G)
#endif

#ifndef _isintwups_
#define _isintwups_
	#define isintwups (L->twups != L)
#endif

#ifndef _uplevel_
#define _uplevel_
	#define uplevel check_exp(upisopen(up), cast(StkId, (up)->v.p))
#endif

#ifndef _isdead_
#define _isdead_
	#define isdead isdeadm(otherwhite(g), (v)->marked)
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

#ifndef _StkId_
#define _StkId_
	typedef StackValue *StkId;
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


void luaF_findupvalFun(void *p);

typedef struct __luaF_findupval
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	UpVal *			ret;
	/* In&Output Variables */
	lua_State*			L;
	StkId			level;
	/* Statement Variables*/
	/* Argument Variables */
} luaF_findupval;

#endif // __LUAF_FINDUPVAL_H__