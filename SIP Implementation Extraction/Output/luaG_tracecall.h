#if !defined(__LUAG_TRACECALL_H__)
#define __LUAG_TRACECALL_H__

#include "common.h"
#include "luaD_hookcall.h"

#ifndef _PF_ISVARARG_
	#define PF_ISVARARG 1
#endif

#ifndef _CIST_HOOKYIELD_
	#define CIST_HOOKYIELD (CIST_TAIL << 1)
#endif

#ifndef _CI_FUNC_
	#define ci_func (clLvalue(s2v((ci)->func.p)))
#endif

struct lua_State;
#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
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

void luaG_tracecallFun(void *p);

typedef struct __luaG_tracecall
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	lua_State*			L;
	/* Statement Variables*/
	/* Argument Variables */
} luaG_tracecall;

#endif // __LUAG_TRACECALL_H__