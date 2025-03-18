#if !defined(__LUAE_CHECKCSTACK_H__)
#define __LUAE_CHECKCSTACK_H__

#include "common.h"
#include "luaG_runerror.h"
#include "luaD_throw.h"

#ifndef _LUA_ERRERR_
	#define LUA_ERRERR 5
#endif

#ifndef _GETCCALLS_
	#define getCcalls ((L)->nCcalls & 0xffff)
#endif

#ifndef _LUAI_MAXCCALLS_
	#define LUAI_MAXCCALLS 200
#endif

struct lua_State;
#ifndef _TSTATUS_
	typedef lu_byte TStatus;
#endif

#ifndef _L_UINT32_
	typedef unsigned int l_uint32;
#endif

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

void luaE_checkcstackFun(void *p);

typedef struct __luaE_checkcstack
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	/* Statement Variables*/
	/* Argument Variables */
} luaE_checkcstack;

#endif // __LUAE_CHECKCSTACK_H__