#if !defined(__MAINPOSITIONFROMNODE_H__)
#define __MAINPOSITIONFROMNODE_H__

#include "common.h"
#include mainpositionTV.h

#ifndef _CAST_
	#define cast ((t)(exp))
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

void mainpositionfromnodeFun(void *p);

typedef struct __mainpositionfromnode
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	/* 输出端口 */
	Node *			ret;
	/* 输入输出端口 */
	const Table*			t;
	Node*			nd;
	/* 状态变量 */
	/* 参数变量 */
} mainpositionfromnode;

#endif // __MAINPOSITIONFROMNODE_H__