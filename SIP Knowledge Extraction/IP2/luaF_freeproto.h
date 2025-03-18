#if !defined(__LUAF_FREEPROTO_H__)
#define __LUAF_FREEPROTO_H__

#include "common.h"
#include luaM_free_.h

#ifndef _CAST_SIZET_
	#define cast_sizet cast(size_t, (i))
#endif

#ifndef _PF_FIXED_
	#define PF_FIXED 2
#endif

#ifndef _LUAM_FREE_
	#define luaM_free luaM_free_(L, (b), sizeof(*(b)))
#endif

#ifndef _LUAM_FREEARRAY_
	#define luaM_freearray luaM_free_(L, (b), (n)*sizeof(*(b)))
#endif

struct lua_State;
#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif

#ifndef _LS_BYTE_
	typedef signed char ls_byte;
#endif

#ifndef _TVALUE_
	struct TValue {
	  TValuefields;
	};
#endif

typedef l_uint32 Instruction;
#ifndef _UPVALDESC_
	struct Upvaldesc {
	  TString *name;  /* upvalue name (for debug information) */
	  lu_byte instack;  /* whether it is in stack (register) */
	  lu_byte idx;  /* index of upvalue (in stack or in outer function's list) */
	  lu_byte kind;  /* kind of corresponding variable */
	};
#endif

#ifndef _LOCVAR_
	struct LocVar {
	  TString *varname;
	  int startpc;  /* first point where variable is active */
	  int endpc;    /* first point where variable is dead */
	};
#endif

#ifndef _ABSLINEINFO_
	struct AbsLineInfo {
	  int pc;
	  int line;
	};
#endif

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

void luaF_freeprotoFun(void *p);

typedef struct __luaF_freeproto
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	/* 输出端口 */
	/* 输入输出端口 */
	lua_State*			L;
	Proto*			f;
	/* 状态变量 */
	/* 参数变量 */
} luaF_freeproto;

#endif // __LUAF_FREEPROTO_H__