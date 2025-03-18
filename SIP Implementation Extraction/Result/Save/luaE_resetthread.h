#if !defined(__LUAE_RESETTHREAD_H__)
#define __LUAE_RESETTHREAD_H__

#include "common.h"
#include "luaD_closeprotected.h"
#include "luaD_seterrorobj.h"
#include "luaD_reallocstack.h"

#ifndef _LUA_OK_
	#define LUA_OK 0
#endif

#ifndef _LUA_YIELD_
	#define LUA_YIELD 1
#endif

#ifndef _LUA_MINSTACK_
	#define LUA_MINSTACK 20
#endif

#ifndef _CAST_INT_
	#define cast_int cast(int, (i))
#endif

#ifndef _S2V_
	#define s2v (&(o)->val)
#endif

#ifndef _SETNILVALUE_
	#define setnilvalue settt_(obj, LUA_VNIL)
#endif

#ifndef _CIST_C_
	#define CIST_C (1u << (CIST_RECST + 3))
#endif

struct lua_State;
#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif

#ifndef _TSTATUS_
	typedef lu_byte TStatus;
#endif

#ifndef _L_UINT32_
	typedef unsigned int l_uint32;
#endif

#ifndef _CALLINFO_
	typedef struct CallInfo CallInfo;
#endif

#ifndef _TVALUE_
	struct TValue {
	  TValuefields;
	};
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

void luaE_resetthreadFun(void *p);

typedef struct __luaE_resetthread
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	TStatus*			ret;
	/* In&Output Variables */
	lua_State*			L;
	TStatus			status;
	/* Statement Variables*/
	/* Argument Variables */
} luaE_resetthread;

#endif // __LUAE_RESETTHREAD_H__