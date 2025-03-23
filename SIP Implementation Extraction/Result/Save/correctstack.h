#if !defined(__CORRECTSTACK_H__)
#define __CORRECTSTACK_H__

#include "common.h"


#ifndef _s2v_
#define _s2v_
	#define s2v (&(o)->val)
#endif

#ifndef _isLua_
#define _isLua_
	#define isLua (!((ci)->callstatus & CIST_C))
#endif

#ifndef _uplevel_
#define _uplevel_
	#define uplevel check_exp(upisopen(up), cast(StkId, (up)->v.p))
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _l_uint32_
#define _l_uint32_
	typedef unsigned int l_uint32;
#endif

#ifndef _CallInfo_
#define _CallInfo_
	typedef struct CallInfo CallInfo;
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

#ifndef _StkIdRel_
#define _StkIdRel_
	union {
	  StkId p;  /* actual pointer */
	  ptrdiff_t offset;  /* used while the stack is being reallocated */
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


void correctstackFun(void *p);

typedef struct __correctstack
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	StkId			oldstack;
	/* Statement Variables*/
	/* Argument Variables */
} correctstack;

#endif // __CORRECTSTACK_H__