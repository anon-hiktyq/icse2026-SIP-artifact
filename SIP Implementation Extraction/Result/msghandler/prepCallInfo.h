#if !defined(__PREPCALLINFO_H__)
#define __PREPCALLINFO_H__

#include "common.h"


#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
#endif

#ifndef _CIST_NRESULTS_
#define _CIST_NRESULTS_
	#define CIST_NRESULTS 0xffu
#endif

#ifndef _MAX_CCMT_
#define _MAX_CCMT_
	#define MAX_CCMT (0xfu << CIST_CCMT)
#endif

#ifndef _CIST_C_
#define _CIST_C_
	#define CIST_C (1u << (CIST_RECST + 3))
#endif

#ifndef _next_ci_
#define _next_ci_
	#define next_ci (L->ci->next ? L->ci->next : luaE_extendCI(L))
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


void prepCallInfoFun(void *p);

typedef struct __prepCallInfo
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	unsigned int			status;
	/* Output Variables */
	CallInfo *			ret;
	/* In&Output Variables */
	lua_State*			L;
	StkId			func;
	StkId			top;
	/* Statement Variables*/
	/* Argument Variables */
} prepCallInfo;

#endif // __PREPCALLINFO_H__