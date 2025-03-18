#if !defined(__AUXGETINFO_H__)
#define __AUXGETINFO_H__

#include "common.h"
#include funcinfo.h
#include getcurrentline.h
#include getfuncname.h

#ifndef _CAST_UCHAR_
	#define cast_uchar cast(unsigned char, (i))
#endif

#ifndef _PF_ISVARARG_
	#define PF_ISVARARG 1
#endif

#ifndef _CIST_CCMT_
	#define CIST_CCMT 8
#endif

#ifndef _MAX_CCMT_
	#define MAX_CCMT (0xfu << CIST_CCMT)
#endif

#ifndef _CIST_HOOKED_
	#define CIST_HOOKED (CIST_OAH << 1)
#endif

#ifndef _CIST_TAIL_
	#define CIST_TAIL (CIST_YPCALL << 1)
#endif

#define isLua (!((ci)->callstatus & CIST_C))
#ifndef _LUACLOSURE_
	#define LuaClosure ((f) != NULL && (f)->c.tt == LUA_VLCL)
#endif

struct lua_State;
#ifndef _LUA_DEBUG_
	struct lua_Debug;
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif

#ifndef _L_UINT32_
	typedef unsigned int l_uint32;
#endif

#ifndef _CALLINFO_
	typedef struct CallInfo CallInfo;
#endif

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
#ifndef _CCLOSURE_
	struct CClosure {
	  ClosureHeader;
	  lua_CFunction f;
	  TValue upvalue[1];  /* list of upvalues */
	};
#endif

struct LClosure {
  ClosureHeader;
  struct Proto *p;
  UpVal *upvals[1];  /* list of upvalues */
};
union Closure {
  CClosure c;
  LClosure l;
};
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

void auxgetinfoFun(void *p);

typedef struct __auxgetinfo
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	int			status;
	int*			ret;
	/* In&Output Variables */
	lua_State*			L;
	const char*			what;
	lua_Debug*			ar;
	Closure*			f;
	CallInfo*			ci;
	/* Statement Variables*/
	/* Argument Variables */
} auxgetinfo;

#endif // __AUXGETINFO_H__