#if !defined(__PRECALLC_H__)
#define __PRECALLC_H__

#include "common.h"
#include "prepCallInfo.h"
#include "luaD_hook.h"
#include "luaD_poscall.h"

#ifndef _l_unlikely_
#define _l_unlikely_
	#define l_unlikely luai_unlikely(x)
#endif

#ifndef _LUA_MINSTACK_
#define _LUA_MINSTACK_
	#define LUA_MINSTACK 20
#endif

#ifndef _LUA_HOOKCALL_
#define _LUA_HOOKCALL_
	#define LUA_HOOKCALL 0
#endif

#ifndef _LUA_MASKCALL_
#define _LUA_MASKCALL_
	#define LUA_MASKCALL (1 << LUA_HOOKCALL)
#endif

#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
#endif

#ifndef _cast_int_
#define _cast_int_
	#define cast_int cast(int, (i))
#endif

#ifndef _CIST_C_
#define _CIST_C_
	#define CIST_C (1u << (CIST_RECST + 3))
#endif

#ifndef _lua_lock_
#define _lua_lock_
	#define lua_lock ((void) 0)
#endif

#ifndef _lua_unlock_
#define _lua_unlock_
	#define lua_unlock ((void) 0)
#endif

#ifndef _api_checknelems_
#define _api_checknelems_
	#define api_checknelems api_check(L, (n) < (L->top.p - L->ci->func.p), \
	                         "not enough elements in the stack")
#endif

#ifndef _checkstackp_
#define _checkstackp_
	#define checkstackp None
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _lua_CFunction_
#define _lua_CFunction_
	typedef int (*lua_CFunction) (lua_State *L);
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


void precallCFun(void *p);

typedef struct __precallC
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	unsigned int			status;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	lua_State*			L;
	StkId			func;
	lua_CFunction			f;
	/* Statement Variables*/
	/* Argument Variables */
} precallC;

#endif // __PRECALLC_H__