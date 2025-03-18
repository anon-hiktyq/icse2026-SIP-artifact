#if !defined(__LUAM_SAFEREALLOC__H__)
#define __LUAM_SAFEREALLOC__H__

#include "common.h"
#include "luaM_realloc_.h"

#ifndef _L_UNLIKELY_
	#define l_unlikely luai_unlikely(x)
#endif

#ifndef _LUAM_ERROR_
	#define luaM_error luaD_throw(L, LUA_ERRMEM)
#endif

struct lua_State;
#ifndef _TSTATUS_
	typedef lu_byte TStatus;
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

void luaM_saferealloc_Fun(void *p);

typedef struct __luaM_saferealloc_
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	size_t			osize;
	size_t			nsize;
	/* Output Variables */
	void *			ret;
	/* In&Output Variables */
	lua_State*			L;
	Unknown type*			block;
	/* Statement Variables*/
	/* Argument Variables */
} luaM_saferealloc_;

#endif // __LUAM_SAFEREALLOC__H__