#if !defined(__LUAT_CALLTMRES_H__)
#define __LUAT_CALLTMRES_H__

#include "common.h"
#include "luaD_call.h"
#include "luaD_callnoyield.h"

#ifndef _ttypetag_
#define _ttypetag_
	#define ttypetag withvariant(rawtt(o))
#endif

#ifndef _setobjs2s_
#define _setobjs2s_
	#define setobjs2s setobj(L,s2v(o1),s2v(o2))
#endif

#ifndef _setobj2s_
#define _setobj2s_
	#define setobj2s setobj(L,s2v(o1),o2)
#endif

#ifndef _s2v_
#define _s2v_
	#define s2v (&(o)->val)
#endif

#ifndef _isLuacode_
#define _isLuacode_
	#define isLuacode (!((ci)->callstatus & (CIST_C | CIST_HOOKED)))
#endif

#ifndef _savestack_
#define _savestack_
	#define savestack (cast_charp(pt) - cast_charp(L->stack.p))
#endif

#ifndef _restorestack_
#define _restorestack_
	#define restorestack cast(StkId, cast_charp(L->stack.p) + (n))
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _CallInfo_
#define _CallInfo_
	typedef struct CallInfo CallInfo;
#endif

#ifndef _lu_byte_
#define _lu_byte_
	typedef unsigned char lu_byte;
#endif

#ifndef _l_uint32_
#define _l_uint32_
	typedef unsigned int l_uint32;
#endif

#ifndef _Value_
#define _Value_
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

#ifndef _TValue_
#define _TValue_
	struct TValue {
	  TValuefields;
	};
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


void luaT_callTMresFun(void *p);

typedef struct __luaT_callTMres
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	lu_byte*			ret;
	/* In&Output Variables */
	lua_State*			L;
	const TValue*			f;
	const TValue*			p1;
	const TValue*			p2;
	StkId			res;
	/* Statement Variables*/
	/* Argument Variables */
} luaT_callTMres;

#endif // __LUAT_CALLTMRES_H__