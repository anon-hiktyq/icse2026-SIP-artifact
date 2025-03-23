#if !defined(__RETPSETCODE_H__)
#define __RETPSETCODE_H__

#include "common.h"


#ifndef _cast_int_
#define _cast_int_
	#define cast_int cast(int, (i))
#endif

#ifndef _isabstkey_
#define _isabstkey_
	#define isabstkey checktag((v), LUA_VABSTKEY)
#endif

#ifndef _HNOTFOUND_
#define _HNOTFOUND_
	#define HNOTFOUND 1
#endif

#ifndef _HFIRSTNODE_
#define _HFIRSTNODE_
	#define HFIRSTNODE 3
#endif

#ifndef _lu_byte_
#define _lu_byte_
	typedef unsigned char lu_byte;
#endif

#ifndef _TValue_
#define _TValue_
	struct TValue {
	  TValuefields;
	};
#endif

#ifndef _Node_
#define _Node_
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

#ifndef _Table_
#define _Table_
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
#endif


void retpsetcodeFun(void *p);

typedef struct __retpsetcode
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	Table*			t;
	const TValue*			slot;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} retpsetcode;

#endif // __RETPSETCODE_H__