#if !defined(__GROWSTRTAB_H__)
#define __GROWSTRTAB_H__

#include "common.h"
#include luaC_fullgc.h
#include luaS_resize.h

#ifndef _L_UNLIKELY_
	#define l_unlikely luai_unlikely(x)
#endif

#ifndef _LUAM_ERROR_
	#define luaM_error luaD_throw(L, LUA_ERRMEM)
#endif

#ifndef _MAXSTRTB_
	#define MAXSTRTB cast_int(luaM_limitN(INT_MAX, TString*))
#endif

struct lua_State;
#ifndef _TSTATUS_
	typedef lu_byte TStatus;
#endif

#ifndef _STRINGTABLE_
	struct stringtable {
	  TString **hash;  /* array of buckets (linked lists of strings) */
	  int nuse;  /* number of elements */
	  int size;  /* number of buckets */
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

void growstrtabFun(void *p);

typedef struct __growstrtab
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	/* 输出端口 */
	/* 输入输出端口 */
	lua_State*			L;
	stringtable*			tb;
	/* 状态变量 */
	/* 参数变量 */
} growstrtab;

#endif // __GROWSTRTAB_H__