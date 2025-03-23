#if !defined(__LUAE_FREETHREAD_H__)
#define __LUAE_FREETHREAD_H__

#include "common.h"
#include "luaF_closeupval.h"
#include "freestack.h"

#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
#endif

#ifndef _luaM_free_
#define _luaM_free_
	#define luaM_free luaM_free_(L, (b), sizeof(*(b)))
#endif

#ifndef _fromstate_
#define _fromstate_
	#define fromstate (cast(LX *, cast(lu_byte *, (L)) - offsetof(LX, l)))
#endif

#ifndef _luai_userstatefree_
#define _luai_userstatefree_
	#define luai_userstatefree ((void)L)
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
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

#ifndef _LX_
#define _LX_
	struct LX {
	  lu_byte extra_[LUA_EXTRASPACE];
	  lua_State l;
	};
#endif


void luaE_freethreadFun(void *p);

typedef struct __luaE_freethread
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	lua_State*			L;
	lua_State*			L1;
	/* Statement Variables*/
	/* Argument Variables */
} luaE_freethread;

#endif // __LUAE_FREETHREAD_H__