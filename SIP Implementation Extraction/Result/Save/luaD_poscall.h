#if !defined(__LUAD_POSCALL_H__)
#define __LUAD_POSCALL_H__

#include "common.h"
#include "rethook.h"
#include "moveresults.h"

#ifndef _l_unlikely_
#define _l_unlikely_
	#define l_unlikely luai_unlikely(x)
#endif

#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
#endif

#ifndef _CIST_NRESULTS_
#define _CIST_NRESULTS_
	#define CIST_NRESULTS 0xffu
#endif

#ifndef _CIST_CLSRET_
#define _CIST_CLSRET_
	#define CIST_CLSRET (CIST_FRESH << 1)
#endif

#ifndef _CIST_TBC_
#define _CIST_TBC_
	#define CIST_TBC (CIST_CLSRET << 1)
#endif

#ifndef _CIST_HOOKED_
#define _CIST_HOOKED_
	#define CIST_HOOKED (CIST_OAH << 1)
#endif

#ifndef _CIST_YPCALL_
#define _CIST_YPCALL_
	#define CIST_YPCALL (CIST_HOOKED << 1)
#endif

#ifndef _CIST_FIN_
#define _CIST_FIN_
	#define CIST_FIN (CIST_HOOKYIELD << 1)
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
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


void luaD_poscallFun(void *p);

typedef struct __luaD_poscall
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			nres;
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	CallInfo*			ci;
	/* Statement Variables*/
	/* Argument Variables */
} luaD_poscall;

#endif // __LUAD_POSCALL_H__