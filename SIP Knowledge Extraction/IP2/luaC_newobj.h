#if !defined(__LUAC_NEWOBJ_H__)
#define __LUAC_NEWOBJ_H__

#include "common.h"
#include luaC_newobjdt.h

struct lua_State;
#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
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

void luaC_newobjFun(void *p);

typedef struct __luaC_newobj
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	lu_byte			tt;
	size_t			sz;
	/* 输出端口 */
	GCObject *			ret;
	/* 输入输出端口 */
	lua_State*			L;
	/* 状态变量 */
	/* 参数变量 */
} luaC_newobj;

#endif // __LUAC_NEWOBJ_H__