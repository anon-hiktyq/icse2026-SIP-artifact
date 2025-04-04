#if !defined(__CCALL_H__)
#define __CCALL_H__

#include "common.h"
#include "luaE_checkcstack.h"
#include "luaD_precall.h"
#include "luaV_execute.h"

#ifndef _l_unlikely_
#define _l_unlikely_
	#define l_unlikely luai_unlikely(x)
#endif

#ifndef _getCcalls_
#define _getCcalls_
	#define getCcalls ((L)->nCcalls & 0xffff)
#endif

#ifndef _CIST_FRESH_
#define _CIST_FRESH_
	#define CIST_FRESH cast(l_uint32, CIST_C << 1)
#endif

#ifndef _checkstackp_
#define _checkstackp_
	#define checkstackp None
#endif

#ifndef _LUAI_MAXCCALLS_
#define _LUAI_MAXCCALLS_
	#define LUAI_MAXCCALLS 200
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


void ccallFun(void *p);

typedef struct __ccall
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			nResults;
	l_uint32			inc;
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	StkId			func;
	/* Statement Variables*/
	/* Argument Variables */
} ccall;

#endif // __CCALL_H__