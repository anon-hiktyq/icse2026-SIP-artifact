#if !defined(__LUA_CALLK_H__)
#define __LUA_CALLK_H__

#include "common.h"
#include luaD_call.h
#include luaD_callnoyield.h

#ifndef _LUA_OK_
	#define LUA_OK 0
#endif

#ifndef _YIELDABLE_
	#define yieldable (((L)->nCcalls & 0xffff0000) == 0)
#endif

#define isLua (!((ci)->callstatus & CIST_C))
#define api_check ((void)(l), lua_assert((e) && msg))
#define lua_lock ((void) 0)
#define lua_unlock ((void) 0)
#ifndef _ADJUSTRESULTS_
	#define adjustresults { if ((nres) <= LUA_MULTRET && L->ci->top.p < L->top.p) \
		L->ci->top.p = L->top.p; }
#endif

#ifndef _API_CHECKPOP_
	#define api_checkpop api_check(L, (n) < L->top.p - L->ci->func.p &&  \
	                     L->tbclist.p < L->top.p - (n), \
				  "not enough free elements in the stack")
#endif

#ifndef _CHECKRESULTS_
	#define checkresults (api_check(L, (nr) == LUA_MULTRET \
	               || (L->ci->top.p - L->top.p >= (nr) - (na)), \
		"results from function overflow current stack size"), \
	      api_check(L, LUA_MULTRET <= (nr) && (nr) <= MAXRESULTS,  \
	                   "invalid number of results"))
#endif

struct lua_State;
#ifndef _LUA_KCONTEXT_
	typedef LUA_KCONTEXT lua_KContext;
#endif

#ifndef _LUA_KFUNCTION_
	typedef int (*lua_KFunction) (lua_State *L, int status, lua_KContext ctx);
#endif

#ifndef _L_UINT32_
	typedef unsigned int l_uint32;
#endif

#ifndef _CALLINFO_
	typedef struct CallInfo CallInfo;
#endif

typedef StackValue *StkId;
union {
  StkId p;  /* actual pointer */
  ptrdiff_t offset;  /* used while the stack is being reallocated */
};
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

void lua_callkFun(void *p);

typedef struct __lua_callk
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			nargs;
	int			nresults;
	lua_KContext			ctx;
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	lua_KFunction			k;
	/* Statement Variables*/
	/* Argument Variables */
} lua_callk;

#endif // __LUA_CALLK_H__