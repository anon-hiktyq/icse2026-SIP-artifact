#if !defined(__LUA_SETTOP_H__)
#define __LUA_SETTOP_H__

#include "common.h"
#include luaF_close.h

#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _S2V_
	#define s2v (&(o)->val)
#endif

#ifndef _SETNILVALUE_
	#define setnilvalue settt_(obj, LUA_VNIL)
#endif

#ifndef _CIST_TBC_
	#define CIST_TBC (CIST_CLSRET << 1)
#endif

#define api_check ((void)(l), lua_assert((e) && msg))
#define lua_lock ((void) 0)
#define lua_unlock ((void) 0)
#ifndef _CLOSEKTOP_
	#define CLOSEKTOP (LUA_ERRERR + 1)
#endif

struct lua_State;
#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif

#ifndef _TSTATUS_
	typedef lu_byte TStatus;
#endif

#ifndef _CALLINFO_
	typedef struct CallInfo CallInfo;
#endif

struct TValue {
  TValuefields;
};
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

void lua_settopFun(void *p);

typedef struct __lua_settop
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			idx;
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	/* Statement Variables*/
	/* Argument Variables */
} lua_settop;

#endif // __LUA_SETTOP_H__