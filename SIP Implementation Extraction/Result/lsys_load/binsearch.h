#if !defined(__BINSEARCH_H__)
#define __BINSEARCH_H__

#include "common.h"
#include "arraykeyisempty.h"

#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
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


void binsearchFun(void *p);

typedef struct __binsearch
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	Table*			array;
	unsigned int			j;
	/* Output Variables */
	unsigned int*			ret;
	/* In&Output Variables */
	unsigned int			i;
	/* Statement Variables*/
	/* Argument Variables */
} binsearch;

#endif // __BINSEARCH_H__