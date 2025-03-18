#if !defined(__KEYINARRAY_H__)
#define __KEYINARRAY_H__

#include "common.h"


#ifndef _TTISINTEGER_
	#define ttisinteger checktag((o), LUA_VNUMINT)
#endif

#ifndef _IVALUE_
	#define ivalue check_exp(ttisinteger(o), val_(o).i)
#endif

#ifndef _IKEYINARRAY_
	#define ikeyinarray checkrange(k, t->asize)
#endif

#ifndef _LUA_INTEGER_
	typedef LUA_INTEGER lua_Integer;
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
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

#ifndef _TVALUE_
	struct TValue {
	  TValuefields;
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

void keyinarrayFun(void *p);

typedef struct __keyinarray
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	Table*			t;
	const TValue*			key;
	/* 输出端口 */
	unsigned int*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} keyinarray;

#endif // __KEYINARRAY_H__