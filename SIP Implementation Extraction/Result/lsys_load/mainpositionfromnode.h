#if !defined(__MAINPOSITIONFROMNODE_H__)
#define __MAINPOSITIONFROMNODE_H__

#include "common.h"
#include "mainpositionTV.h"

#ifndef _cast_
#define _cast_
	#define cast ((t)(exp))
#endif

#ifndef _lu_byte_
#define _lu_byte_
	typedef unsigned char lu_byte;
#endif

#ifndef _Value_
#define _Value_
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


void mainpositionfromnodeFun(void *p);

typedef struct __mainpositionfromnode
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	Node *			ret;
	/* In&Output Variables */
	const Table*			t;
	Node*			nd;
	/* Statement Variables*/
	/* Argument Variables */
} mainpositionfromnode;

#endif // __MAINPOSITIONFROMNODE_H__