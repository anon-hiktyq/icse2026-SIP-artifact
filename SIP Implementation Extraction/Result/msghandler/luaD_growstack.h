#if !defined(__LUAD_GROWSTACK_H__)
#define __LUAD_GROWSTACK_H__

#include "common.h"
#include "luaD_throw.h"
#include "luaD_reallocstack.h"
#include "luaG_runerror.h"

#ifndef _l_likely_
#define _l_likely_
	#define l_likely luai_likely(x)
#endif

#ifndef _l_unlikely_
#define _l_unlikely_
	#define l_unlikely luai_unlikely(x)
#endif

#ifndef _LUA_ERRERR_
#define _LUA_ERRERR_
	#define LUA_ERRERR 5
#endif

#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
#endif

#ifndef _cast_int_
#define _cast_int_
	#define cast_int cast(int, (i))
#endif

#ifndef _stacksize_
#define _stacksize_
	#define stacksize cast_int((th)->stack_last.p - (th)->stack.p)
#endif

#ifndef _MAXSTACK_
#define _MAXSTACK_
	#define MAXSTACK cast_int(LUAI_MAXSTACK < MAXSTACK_BYSIZET  \
				        ? LUAI_MAXSTACK : MAXSTACK_BYSIZET)
#endif

#ifndef _ERRORSTACKSIZE_
#define _ERRORSTACKSIZE_
	#define ERRORSTACKSIZE (MAXSTACK + STACKERRSPACE)
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _TStatus_
#define _TStatus_
	typedef lu_byte TStatus;
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


void luaD_growstackFun(void *p);

typedef struct __luaD_growstack
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			n;
	int			raiseerror;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	lua_State*			L;
	/* Statement Variables*/
	/* Argument Variables */
} luaD_growstack;

#endif // __LUAD_GROWSTACK_H__