#if !defined(__GETGENERIC_H__)
#define __GETGENERIC_H__

#include "common.h"
#include mainpositionTV.h
#include equalkey.h

#ifndef _GVAL_
	#define gval (&(n)->i_val)
#endif

#ifndef _GNEXT_
	#define gnext ((n)->u.next)
#endif

struct TValue {
  TValuefields;
};
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

void getgenericFun(void *p);

typedef struct __getgeneric
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			deadok;
	/* Output Variables */
	const TValue *			ret;
	/* In&Output Variables */
	Table*			t;
	const TValue*			key;
	/* Statement Variables*/
	/* Argument Variables */
} getgeneric;

#endif // __GETGENERIC_H__