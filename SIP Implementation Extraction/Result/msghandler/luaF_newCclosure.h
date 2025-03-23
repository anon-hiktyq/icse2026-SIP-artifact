#if !defined(__LUAF_NEWCCLOSURE_H__)
#define __LUAF_NEWCCLOSURE_H__

#include "common.h"
#include "luaC_newobj.h"

#ifndef _cast_byte_
#define _cast_byte_
	#define cast_byte cast(lu_byte, (i))
#endif

#ifndef _LUA_VCCL_
#define _LUA_VCCL_
	#define LUA_VCCL makevariant(LUA_TFUNCTION, 2)
#endif

#ifndef _gco2ccl_
#define _gco2ccl_
	#define gco2ccl check_exp((o)->tt == LUA_VCCL, &((cast_u(o))->cl.c))
#endif

#ifndef _sizeCclosure_
#define _sizeCclosure_
	#define sizeCclosure (offsetof(CClosure, upvalue) + sizeof(TValue) * cast_uint(n))
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _lu_byte_
#define _lu_byte_
	typedef unsigned char lu_byte;
#endif

#ifndef _GCObject_
#define _GCObject_
	struct GCObject {
	  CommonHeader;
	};
#endif

#ifndef _CClosure_
#define _CClosure_
	struct CClosure {
	  ClosureHeader;
	  lua_CFunction f;
	  TValue upvalue[1];  /* list of upvalues */
	};
#endif

#ifndef _Closure_
#define _Closure_
	union Closure {
	  CClosure c;
	  LClosure l;
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


void luaF_newCclosureFun(void *p);

typedef struct __luaF_newCclosure
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			nupvals;
	/* Output Variables */
	CClosure *			ret;
	/* In&Output Variables */
	lua_State*			L;
	/* Statement Variables*/
	/* Argument Variables */
} luaF_newCclosure;

#endif // __LUAF_NEWCCLOSURE_H__