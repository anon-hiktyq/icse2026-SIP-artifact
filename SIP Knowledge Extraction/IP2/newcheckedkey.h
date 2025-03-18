#if !defined(__NEWCHECKEDKEY_H__)
#define __NEWCHECKEDKEY_H__

#include "common.h"
#include keyinarray.h
#include insertkey.h

#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _CAST_
	#define cast ((t)(exp))
#endif

#ifndef _OBJ2ARR_
	#define obj2arr (*getArrTag(h,(k)) = (val)->tt_, *getArrVal(h,(k)) = (val)->value_)
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

void newcheckedkeyFun(void *p);

typedef struct __newcheckedkey
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	/* 输出端口 */
	/* 输入输出端口 */
	Table*			t;
	const TValue*			key;
	TValue*			value;
	/* 状态变量 */
	/* 参数变量 */
} newcheckedkey;

#endif // __NEWCHECKEDKEY_H__