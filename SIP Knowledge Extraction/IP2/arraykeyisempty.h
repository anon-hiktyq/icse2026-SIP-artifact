#if !defined(__ARRAYKEYISEMPTY_H__)
#define __ARRAYKEYISEMPTY_H__

#include "common.h"


#ifndef _TAGISEMPTY_
	#define tagisempty (novariant(tag) == LUA_TNIL)
#endif

#ifndef _GETARRTAG_
	#define getArrTag (cast(lu_byte*, (t)->array) + sizeof(unsigned) + (k))
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

void arraykeyisemptyFun(void *p);

typedef struct __arraykeyisempty
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	const Table*			t;
	unsigned int			key;
	/* 输出端口 */
	int*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} arraykeyisempty;

#endif // __ARRAYKEYISEMPTY_H__