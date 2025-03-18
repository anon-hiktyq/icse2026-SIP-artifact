#if !defined(__LUAD_PRECALL_H__)
#define __LUAD_PRECALL_H__

#include "common.h"
#include precallC.h
#include prepCallInfo.h
#include tryfuncTM.h

#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _CAST_INT_
	#define cast_int cast(int, (i))
#endif

#ifndef _CAST_UINT_
	#define cast_uint cast(unsigned int, (i))
#endif

#ifndef _TTYPETAG_
	#define ttypetag withvariant(rawtt(o))
#endif

#ifndef _S2V_
	#define s2v (&(o)->val)
#endif

#ifndef _SETNILVALUE_
	#define setnilvalue settt_(obj, LUA_VNIL)
#endif

#ifndef _LUA_VLCL_
	#define LUA_VLCL makevariant(LUA_TFUNCTION, 0)
#endif

#ifndef _LUA_VLCF_
	#define LUA_VLCF makevariant(LUA_TFUNCTION, 1)
#endif

#ifndef _LUA_VCCL_
	#define LUA_VCCL makevariant(LUA_TFUNCTION, 2)
#endif

#ifndef _CLLVALUE_
	#define clLvalue check_exp(ttisLclosure(o), gco2lcl(val_(o).gc))
#endif

#ifndef _FVALUE_
	#define fvalue check_exp(ttislcf(o), val_(o).f)
#endif

#ifndef _CLCVALUE_
	#define clCvalue check_exp(ttisCclosure(o), gco2ccl(val_(o).gc))
#endif

#ifndef _MAXRESULTS_
	#define MAXRESULTS 250
#endif

#ifndef _CHECKSTACKP_
	#define checkstackp None
#endif

struct lua_State;
#ifndef _LUA_CFUNCTION_
	typedef int (*lua_CFunction) (lua_State *L);
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
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

#ifndef _GCOBJECT_
	struct GCObject {
	  CommonHeader;
	};
#endif

typedef l_uint32 Instruction;
#ifndef _PROTO_
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

#ifndef _CCLOSURE_
	struct CClosure {
	  ClosureHeader;
	  lua_CFunction f;
	  TValue upvalue[1];  /* list of upvalues */
	};
#endif

#ifndef _LCLOSURE_
	struct LClosure {
	  ClosureHeader;
	  struct Proto *p;
	  UpVal *upvals[1];  /* list of upvalues */
	};
#endif

#ifndef _CLOSURE_
	union Closure {
	  CClosure c;
	  LClosure l;
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

void luaD_precallFun(void *p);

typedef struct __luaD_precall
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	int			nresults;
	/* 输出端口 */
	CallInfo *			ret;
	/* 输入输出端口 */
	lua_State*			L;
	StkId			func;
	/* 状态变量 */
	/* 参数变量 */
} luaD_precall;

#endif // __LUAD_PRECALL_H__