#if !defined(__LUAD_CALLNOYIELD_H__)
#define __LUAD_CALLNOYIELD_H__

#include "common.h"
#include "ccall.h"

#ifndef _nyci_
#define _nyci_
	#define nyci (0x10000 | 1)
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _l_uint32_
#define _l_uint32_
	typedef unsigned int l_uint32;
#endif

#ifndef _StkId_
#define _StkId_
	typedef StackValue *StkId;
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


void luaD_callnoyieldFun(void *p);

typedef struct __luaD_callnoyield
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			nResults;
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	StkId			func;
	/* Statement Variables*/
	/* Argument Variables */
} luaD_callnoyield;

#endif // __LUAD_CALLNOYIELD_H__