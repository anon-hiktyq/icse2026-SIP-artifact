#if !defined(__LUAG_TRACEEXEC_H__)
#define __LUAG_TRACEEXEC_H__

#include "common.h"
#include "luaP_isIT.h"
#include "luaD_hook.h"
#include "changedline.h"
#include "luaG_getfuncline.h"
#include "luaD_throw.h"

#ifndef _LUA_YIELD_
#define _LUA_YIELD_
	#define LUA_YIELD 1
#endif

#ifndef _LUA_HOOKLINE_
#define _LUA_HOOKLINE_
	#define LUA_HOOKLINE 2
#endif

#ifndef _LUA_HOOKCOUNT_
#define _LUA_HOOKCOUNT_
	#define LUA_HOOKCOUNT 3
#endif

#ifndef _LUA_MASKLINE_
#define _LUA_MASKLINE_
	#define LUA_MASKLINE (1 << LUA_HOOKLINE)
#endif

#ifndef _LUA_MASKCOUNT_
#define _LUA_MASKCOUNT_
	#define LUA_MASKCOUNT (1 << LUA_HOOKCOUNT)
#endif

#ifndef _cast_byte_
#define _cast_byte_
	#define cast_byte cast(lu_byte, (i))
#endif

#ifndef _CIST_HOOKYIELD_
#define _CIST_HOOKYIELD_
	#define CIST_HOOKYIELD (CIST_TAIL << 1)
#endif

#ifndef _pcRel_
#define _pcRel_
	#define pcRel (cast_int((pc) - (p)->code) - 1)
#endif

#ifndef _ci_func_
#define _ci_func_
	#define ci_func (clLvalue(s2v((ci)->func.p)))
#endif

#ifndef _resethookcount_
#define _resethookcount_
	#define resethookcount (L->hookcount = L->basehookcount)
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _lu_byte_
#define _lu_byte_
	typedef unsigned char lu_byte;
#endif

#ifndef _TStatus_
#define _TStatus_
	typedef lu_byte TStatus;
#endif

#ifndef _l_uint32_
#define _l_uint32_
	typedef unsigned int l_uint32;
#endif

#ifndef _CallInfo_
#define _CallInfo_
	typedef struct CallInfo CallInfo;
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

#ifndef _GCObject_
#define _GCObject_
	struct GCObject {
	  CommonHeader;
	};
#endif

#ifndef _Inion_
#define _Inion_
	typedef l_uint32 Instruction;
#endif

#ifndef _Proto_
#define _Proto_
	struct Proto {
	  CommonHeader;
	  lu_byte numparams;  /* number of fixed (named) parameters */
	  lu_byte flag;
	  lu_byte maxstacksize;  /* number of registers needed by this function */
	  int sizeupvalues;  /* size of 'upvalues' */
	  int sizek;  /* size of 'k' */
	  int sizecode;
	  int sizelineinfo;
	  int sizep;  /* size of 'p' */
	  int sizelocvars;
	  int sizeabslineinfo;  /* size of 'abslineinfo' */
	  int linedefined;  /* debug information  */
	  int lastlinedefined;  /* debug information  */
	  TValue *k;  /* constants used by the function */
	  Instruction *code;  /* opcodes */
	  struct Proto **p;  /* functions defined inside the function */
	  Upvaldesc *upvalues;  /* upvalue information */
	  ls_byte *lineinfo;  /* information about source lines (debug information) */
	  AbsLineInfo *abslineinfo;  /* idem */
	  LocVar *locvars;  /* information about local variables (debug information) */
	  TString  *source;  /* used for debug information */
	  GCObject *gclist;
	};
#endif

#ifndef _LClosure_
#define _LClosure_
	struct LClosure {
	  ClosureHeader;
	  struct Proto *p;
	  UpVal *upvals[1];  /* list of upvalues */
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


void luaG_traceexecFun(void *p);

typedef struct __luaG_traceexec
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	lua_State*			L;
	const Instruction*			pc;
	/* Statement Variables*/
	/* Argument Variables */
} luaG_traceexec;

#endif // __LUAG_TRACEEXEC_H__