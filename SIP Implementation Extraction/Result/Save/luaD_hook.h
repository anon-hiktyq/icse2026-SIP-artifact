#if !defined(__LUAD_HOOK_H__)
#define __LUAD_HOOK_H__

#include "common.h"


#ifndef _LUA_MINSTACK_
#define _LUA_MINSTACK_
	#define LUA_MINSTACK 20
#endif

#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
#endif

#ifndef _CIST_HOOKED_
#define _CIST_HOOKED_
	#define CIST_HOOKED (CIST_OAH << 1)
#endif

#ifndef _isLua_
#define _isLua_
	#define isLua (!((ci)->callstatus & CIST_C))
#endif

#ifndef _lua_lock_
#define _lua_lock_
	#define lua_lock ((void) 0)
#endif

#ifndef _lua_unlock_
#define _lua_unlock_
	#define lua_unlock ((void) 0)
#endif

#ifndef _luaD_checkstack_
#define _luaD_checkstack_
	#define luaD_checkstack luaD_checkstackaux(L,n,(void)0,(void)0)
#endif

#ifndef _savestack_
#define _savestack_
	#define savestack (cast_charp(pt) - cast_charp(L->stack.p))
#endif

#ifndef _restorestack_
#define _restorestack_
	#define restorestack cast(StkId, cast_charp(L->stack.p) + (n))
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _lua_Debug_
#define _lua_Debug_
	struct lua_Debug;
#endif

#ifndef _lua_Hook_
#define _lua_Hook_
	typedef void (*lua_Hook) (lua_State *L, lua_Debug *ar);
#endif

#ifndef _lu_byte_
#define _lu_byte_
	typedef unsigned char lu_byte;
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