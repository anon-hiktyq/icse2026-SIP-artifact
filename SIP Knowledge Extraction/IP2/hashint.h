#if !defined(__HASHINT_H__)
#define __HASHINT_H__

#include "common.h"


#ifndef _CAST_INT_
	#define cast_int cast(int, (i))
#endif

#ifndef _CAST_UINT_
	#define cast_uint cast(unsigned int, (i))
#endif

#ifndef _L_CASTS2U_
	#define l_castS2U ((lua_Unsigned)(i))
#endif

#ifndef _SIZENODE_
	#define sizenode (twoto((t)->lsizenode))
#endif

#ifndef _GNODE_
	#define gnode (&(t)->node[i])
#endif

#ifndef _HASHMOD_
	#define hashmod (gnode(t, ((n) % ((sizenode(t)-1u)|1u))))
#endif

#ifndef _LUA_INTEGER_
	typedef LUA_INTEGER lua_Integer;
#endif

#ifndef _LUA_UNSIGNED_
	typedef LUA_UNSIGNED lua_Unsigned;
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
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

void hashintFun(void *p);

typedef struct __hashint
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	const Table*			t;
	lua_Integer			i;
	/* 输出端口 */
	Node *			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} hashint;

#endif // __HASHINT_H__