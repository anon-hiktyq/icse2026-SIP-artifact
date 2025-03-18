#if !defined(__NUMUSEHASH_H__)
#define __NUMUSEHASH_H__

#include "common.h"
#include countint.h

#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _ISEMPTY_
	#define isempty ttisnil(v)
#endif

#ifndef _KEYISNIL_
	#define keyisnil (keytt(node) == LUA_TNIL)
#endif

#ifndef _KEYISINTEGER_
	#define keyisinteger (keytt(node) == LUA_VNUMINT)
#endif

#ifndef _KEYIVAL_
	#define keyival (keyval(node).i)
#endif

#ifndef _SIZENODE_
	#define sizenode (twoto((t)->lsizenode))
#endif

#ifndef _GVAL_
	#define gval (&(n)->i_val)
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

#ifndef _NODE_
	union Node {
	  struct NodeKey {
	    TValuefields;  /* fields for value */
	    lu_byte key_tt;  /* key type */
	    int next;  /* for chaining */
	    Value key_val;  /* key value */
	  } u;
	  TValue i_val;  /* direct access to node's value as a proper 'TValue' */
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
#ifndef _COUNTERS_
	struct {
	  unsigned total;
	  unsigned na;
	  int deleted;
	  unsigned nums[MAXABITS + 1];
	};
#endif


void numusehashFun(void *p);

typedef struct __numusehash
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	const Table*			t;
	/* 输出端口 */
	/* 输入输出端口 */
	Counters*			ct;
	/* 状态变量 */
	/* 参数变量 */
} numusehash;

#endif // __NUMUSEHASH_H__