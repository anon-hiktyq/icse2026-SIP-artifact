#if !defined(__LUAE_THREADSIZE_H__)
#define __LUAE_THREADSIZE_H__

#include "common.h"


#ifndef _cast_
#define _cast_
	#define cast ((t)(exp))
#endif

#ifndef _cast_uint_
#define _cast_uint_
	#define cast_uint cast(unsigned int, (i))
#endif

#ifndef _EXTRA_STACK_
#define _EXTRA_STACK_
	#define EXTRA_STACK 5
#endif

#ifndef _stacksize_
#define _stacksize_
	#define stacksize cast_int((th)->stack_last.p - (th)->stack.p)
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _lu_mem_
#define _lu_mem_
	typedef size_t lu_mem;
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


void luaE_threadsizeFun(void *p);

typedef struct __luaE_threadsize
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	lua_State*			L;
	/* Output Variables */
	lu_mem*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} luaE_threadsize;

#endif // __LUAE_THREADSIZE_H__