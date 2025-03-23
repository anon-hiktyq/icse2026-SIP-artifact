#if !defined(__LUAD_PRETAILCALL_H__)
#define __LUAD_PRETAILCALL_H__

#include "common.h"
#include "precallC.h"
#include "luaD_growstack.h"
#include "tryfuncTM.h"

#ifndef _LUA_MULTRET_
#define _LUA_MULTRET_
	#define LUA_MULTRET (-1)
#endif

#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
#endif

#ifndef _ttypetag_
#define _ttypetag_
	#define ttypetag withvariant(rawtt(o))
#endif

#ifndef _setobjs2s_
#define _setobjs2s_
	#define setobjs2s setobj(L,s2v(o1),s2v(o2))
#endif

#ifndef _s2v_
#define _s2v_
	#define s2v (&(o)->val)
#endif

#ifndef _setnilvalue_
#define _setnilvalue_
	#define setnilvalue settt_(obj, LUA_VNIL)
#endif

#ifndef _LUA_VLCL_
#define _LUA_VLCL_
	#define LUA_VLCL makevariant(LUA_TFUNCTION, 0)
#endif

#ifndef _LUA_VLCF_
#define _LUA_VLCF_
	#define LUA_VLCF makevariant(LUA_TFUNCTION, 1)
#endif

#ifndef _LUA_VCCL_
#define _LUA_VCCL_
	#define LUA_VCCL makevariant(LUA_TFUNCTION, 2)
#endif

#ifndef _clLvalue_
#define _clLvalue_
	#define clLvalue check_exp(ttisLclosure(o), gco2lcl(val_(o).gc))
#endif

#ifndef _fvalue_
#define _fvalue_
	#define fvalue check_exp(ttislcf(o), val_(o).f)
#endif

#ifndef _clCvalue_
#define _clCvalue_
	#define clCvalue check_exp(ttisCclosure(o), gco2ccl(val_(o).gc))
#endif

#ifndef _CIST_TAIL_
#define _CIST_TAIL_
	#define CIST_TAIL (CIST_YPCALL << 1)
#endif

#ifndef _checkstackp_
#define _checkstackp_
	#define checkstackp None
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _lua_CFunction_
#define _lua_CFunction_
	typedef int (*lua_CFunction) (lua_State *L);
#endif

#ifndef _lu_byte_
#define _lu_byte_
	typedef unsigned char lu_byte;
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

#ifndef _CClosure_
#define _CClosure_
	struct CClosure {
	  ClosureHeader;
	  lua_CFunction f;
	  TValue upvalue[1];  /* list of upvalues */
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


void luaD_pretailcallFun(void *p);

typedef struct __luaD_pretailcall
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			narg1;
	int			delta;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	lua_State*			L;
	CallInfo*			ci;
	StkId			func;
	/* Statement Variables*/
	/* Argument Variables */
} luaD_pretailcall;

#endif // __LUAD_PRETAILCALL_H__