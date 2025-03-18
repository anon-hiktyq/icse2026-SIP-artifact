#if !defined(__RESIZEARRAY_H__)
#define __RESIZEARRAY_H__

#include "common.h"
#include concretesize.h

#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _CAST_
	#define cast ((t)(exp))
#endif

#ifndef _LUAM_FREEMEM_
	#define luaM_freemem luaM_free_(L, (b), (s))
#endif

#ifndef _LUAM_REALLOCVECTOR_
	#define luaM_reallocvector (cast(t *, luaM_realloc_(L, v, cast_sizet(oldn) * sizeof(t), \
	                                  cast_sizet(n) * sizeof(t))))
#endif

struct lua_State;
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

struct Table {
  CommonHeader;
  lu_byte flags;  /* 1<<p means tagmethod(p) is not present */
  lu_byte lsizenode;  /* log2 of number of slots of 'node' array */
  unsigned int asize;  /* number of slots in 'array' array */
  Value *array;  /* array part */
  Node *node;
  struct Table *metatable;
  GCObject *gclist;
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

void resizearrayFun(void *p);

typedef struct __resizearray
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	unsigned int			oldasize;
	unsigned int			newasize;
	/* 输出端口 */
	Value *			ret;
	/* 输入输出端口 */
	lua_State*			L;
	Table*			t;
	/* 状态变量 */
	/* 参数变量 */
} resizearray;

#endif // __RESIZEARRAY_H__