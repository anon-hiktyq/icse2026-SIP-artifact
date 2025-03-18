#if !defined(__LUAH_PSETINT_H__)
#define __LUAH_PSETINT_H__

#include "common.h"
#include finishnodeset.h

#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _IKEYINARRAY_
	#define ikeyinarray checkrange(k, t->asize)
#endif

#ifndef _LUA_INTEGER_
	typedef LUA_INTEGER lua_Integer;
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

void luaH_psetintFun(void *p);

typedef struct __luaH_psetint
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	lua_Integer			key;
	/* 输出端口 */
	int*			ret;
	/* 输入输出端口 */
	Table*			t;
	TValue*			val;
	/* 状态变量 */
	/* 参数变量 */
} luaH_psetint;

#endif // __LUAH_PSETINT_H__