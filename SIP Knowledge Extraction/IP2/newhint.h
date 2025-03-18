#if !defined(__NEWHINT_H__)
#define __NEWHINT_H__

#include "common.h"


#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _LENHINT_
	#define lenhint cast(unsigned*, (t)->array)
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

void newhintFun(void *p);

typedef struct __newhint
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	unsigned int			hint;
	/* 输出端口 */
	lua_Unsigned*			ret;
	/* 输入输出端口 */
	Table*			t;
	/* 状态变量 */
	/* 参数变量 */
} newhint;

#endif // __NEWHINT_H__