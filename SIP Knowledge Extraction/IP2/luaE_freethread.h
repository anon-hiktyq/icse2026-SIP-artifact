#if !defined(__LUAE_FREETHREAD_H__)
#define __LUAE_FREETHREAD_H__

#include "common.h"
#include luaF_closeupval.h
#include freestack.h

#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _LUAM_FREE_
	#define luaM_free luaM_free_(L, (b), sizeof(*(b)))
#endif

#ifndef _FROMSTATE_
	#define fromstate (cast(LX *, cast(lu_byte *, (L)) - offsetof(LX, l)))
#endif

#ifndef _LUAI_USERSTATEFREE_
	#define luai_userstatefree ((void)L)
#endif

struct lua_State;
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
#ifndef _LX_
	struct LX {
	  lu_byte extra_[LUA_EXTRASPACE];
	  lua_State l;
	};
#endif


void luaE_freethreadFun(void *p);

typedef struct __luaE_freethread
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	/* 输出端口 */
	/* 输入输出端口 */
	lua_State*			L;
	lua_State*			L1;
	/* 状态变量 */
	/* 参数变量 */
} luaE_freethread;

#endif // __LUAE_FREETHREAD_H__