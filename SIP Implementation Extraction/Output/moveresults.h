#if !defined(__MOVERESULTS_H__)
#define __MOVERESULTS_H__

#include "common.h"
#include "genmoveresults.h"
#include "luaF_close.h"
#include "rethook.h"

#ifndef _LUA_MULTRET_
	#define LUA_MULTRET (-1)
#endif

#ifndef _SETOBJS2S_
	#define setobjs2s setobj(L,s2v(o1),s2v(o2))
#endif

#ifndef _S2V_
	#define s2v (&(o)->val)
#endif

#ifndef _SETNILVALUE_
	#define setnilvalue settt_(obj, LUA_VNIL)
#endif

#ifndef _CIST_CLSRET_
	#define CIST_CLSRET (CIST_FRESH << 1)
#endif

#ifndef _CIST_TBC_
	#define CIST_TBC (CIST_CLSRET << 1)
#endif

#ifndef _GET_NRESULTS_
	#define get_nresults (cast_int((cs) & CIST_NRESULTS) - 1)
#endif

#ifndef _SAVESTACK_
	#define savestack (cast_charp(pt) - cast_charp(L->stack.p))
#endif

#ifndef _RESTORESTACK_
	#define restorestack cast(StkId, cast_charp(L->stack.p) + (n))
#endif

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

#ifndef _L_UINT32_
	typedef unsigned int l_uint32;
#endif

#ifndef _CALLINFO_
	typedef struct CallInfo CallInfo;
#endif

#ifndef _VALUE_
	union Value {
	  struct GCObject *gc;    /* collectable objects */
	  void *p;         /* light userdata */
	  lua_CFunction f; /* light C functions */
	  lua_Integer i;   /* integer numbers */
	  lua_Number n;    /* float numbers */
	  /* not used, but may avoid warnings for uninitialized value */
	  lu_byte ub;
	};
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

void moveresultsFun(void *p);

typedef struct __moveresults
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			nres;
	l_uint32			fwanted;
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	StkId			res;
	/* Statement Variables*/
	/* Argument Variables */
} moveresults;

#endif // __MOVERESULTS_H__