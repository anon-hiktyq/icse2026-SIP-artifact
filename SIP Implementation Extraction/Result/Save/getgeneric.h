#if !defined(__GETGENERIC_H__)
#define __GETGENERIC_H__

#include "common.h"
#include "mainpositionTV.h"
#include "equalkey.h"

#ifndef _gval_
#define _gval_
	#define gval (&(n)->i_val)
#endif

#ifndef _gnext_
#define _gnext_
	#define gnext ((n)->u.next)
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