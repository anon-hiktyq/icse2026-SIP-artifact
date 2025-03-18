#if !defined(__LUAD_RAWRUNPROTECTED_H__)
#define __LUAD_RAWRUNPROTECTED_H__

#include "common.h"


#ifndef _LUA_OK_
	#define LUA_OK 0
#endif

#ifndef _LUAI_TRY_
	#define LUAI_TRY if (setjmp((c)->b) == 0) ((f)(L, ud))
#endif

struct lua_State;
#ifndef _TSTATUS_
	typedef lu_byte TStatus;
#endif

#ifndef _L_UINT32_
	typedef unsigned int l_uint32;
#endif

#ifndef _LUA_LONGJMP_
	struct lua_longjmp;
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
#ifndef _PFUNC_
	typedef void (*Pfunc) (lua_State *L, void *ud);
#endif

#ifndef _LUA_LONGJMP_
	struct lua_longjmp {
	  struct lua_longjmp *previous;
	  luai_jmpbuf b;
	  volatile TStatus status;  /* error code */
	};
#endif


void luaD_rawrunprotectedFun(void *p);

typedef struct __luaD_rawrunprotected
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	Pfunc			f;
	/* Output Variables */
	TStatus*			ret;
	/* In&Output Variables */
	lua_State*			L;
	Unknown type*			ud;
	/* Statement Variables*/
	/* Argument Variables */
} luaD_rawrunprotected;

#endif // __LUAD_RAWRUNPROTECTED_H__