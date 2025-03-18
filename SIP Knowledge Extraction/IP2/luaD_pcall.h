#if !defined(__LUAD_PCALL_H__)
#define __LUAD_PCALL_H__

#include "common.h"
#include luaD_rawrunprotected.h
#include luaD_closeprotected.h
#include luaD_seterrorobj.h
#include luaD_shrinkstack.h

#ifndef _L_UNLIKELY_
	#define l_unlikely luai_unlikely(x)
#endif

#ifndef _LUA_OK_
	#define LUA_OK 0
#endif

#ifndef _RESTORESTACK_
	#define restorestack cast(StkId, cast_charp(L->stack.p) + (n))
#endif

struct lua_State;
#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif

#ifndef _TSTATUS_
	typedef lu_byte TStatus;
#endif

#ifndef _CALLINFO_
	typedef struct CallInfo CallInfo;
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
#ifndef _PFUNC_
	typedef void (*Pfunc) (lua_State *L, void *ud);
#endif


void luaD_pcallFun(void *p);

typedef struct __luaD_pcall
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	Pfunc			func;
	ptrdiff_t			old_top;
	ptrdiff_t			ef;
	/* 输出端口 */
	TStatus			status;
	TStatus*			ret;
	/* 输入输出端口 */
	lua_State*			L;
	Unknown type*			u;
	/* 状态变量 */
	/* 参数变量 */
} luaD_pcall;

#endif // __LUAD_PCALL_H__