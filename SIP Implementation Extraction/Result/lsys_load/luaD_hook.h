#if !defined(__LUAD_HOOK_H__)
#define __LUAD_HOOK_H__

#include "common.h"


#ifndef _LUA_MINSTACK_
	#define LUA_MINSTACK 20
#endif

#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _CIST_HOOKED_
	#define CIST_HOOKED (CIST_OAH << 1)
#endif

#define isLua (!((ci)->callstatus & CIST_C))
#ifndef _LUA_LOCK_
	#define lua_lock ((void) 0)
#endif

#ifndef _LUA_UNLOCK_
	#define lua_unlock ((void) 0)
#endif

#ifndef _LUAD_CHECKSTACK_
	#define luaD_checkstack luaD_checkstackaux(L,n,(void)0,(void)0)
#endif

#ifndef _SAVESTACK_
	#define savestack (cast_charp(pt) - cast_charp(L->stack.p))
#endif

#ifndef _RESTORESTACK_
	#define restorestack cast(StkId, cast_charp(L->stack.p) + (n))
#endif

struct lua_State;
#ifndef _LUA_DEBUG_
	struct lua_Debug;
#endif

#ifndef _LUA_HOOK_
	typedef void (*lua_Hook) (lua_State *L, lua_Debug *ar);
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif

#ifndef _L_UINT32_
	typedef unsigned int l_uint32;
#endif

#ifndef _CALLINFO_
	typedef struct CallInfo CallInfo;
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


void luaD_hookFun(void *p);

typedef struct __luaD_hook
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			event;
	int			line;
	int			ftransfer;
	int			ntransfer;
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	/* Statement Variables*/
	/* Argument Variables */
} luaD_hook;

#endif // __LUAD_HOOK_H__