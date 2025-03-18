#if !defined(__RETPSETCODE_H__)
#define __RETPSETCODE_H__

#include "common.h"


#ifndef _CAST_INT_
	#define cast_int cast(int, (i))
#endif

#ifndef _ISABSTKEY_
	#define isabstkey checktag((v), LUA_VABSTKEY)
#endif

#ifndef _HNOTFOUND_
	#define HNOTFOUND 1
#endif

#ifndef _HFIRSTNODE_
	#define HFIRSTNODE 3
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
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

void retpsetcodeFun(void *p);

typedef struct __retpsetcode
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	Table*			t;
	const TValue*			slot;
	/* 输出端口 */
	int*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} retpsetcode;

#endif // __RETPSETCODE_H__