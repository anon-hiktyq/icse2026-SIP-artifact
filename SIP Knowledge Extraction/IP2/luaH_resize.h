#if !defined(__LUAH_RESIZE_H__)
#define __LUAH_RESIZE_H__

#include "common.h"
#include luaG_runerror.h
#include setnodevector.h
#include exchangehashpart.h
#include reinsertOldSlice.h
#include resizearray.h
#include freehash.h
#include clearNewSlice.h
#include reinserthash.h

#ifndef _L_UNLIKELY_
	#define l_unlikely luai_unlikely(x)
#endif

#ifndef _LUAM_ERROR_
	#define luaM_error luaD_throw(L, LUA_ERRMEM)
#endif

#ifndef _LENHINT_
	#define lenhint cast(unsigned*, (t)->array)
#endif

#ifndef _MAXASIZE_
	#define MAXASIZE (((1u << MAXABITS) < MAXASIZEB) ? (1u << MAXABITS) : cast_uint(MAXASIZEB))
#endif

struct lua_State;
#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif

#ifndef _TSTATUS_
	typedef lu_byte TStatus;
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

void luaH_resizeFun(void *p);

typedef struct __luaH_resize
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	unsigned int			newasize;
	unsigned int			nhsize;
	/* 输出端口 */
	/* 输入输出端口 */
	lua_State*			L;
	Table*			t;
	/* 状态变量 */
	/* 参数变量 */
} luaH_resize;

#endif // __LUAH_RESIZE_H__