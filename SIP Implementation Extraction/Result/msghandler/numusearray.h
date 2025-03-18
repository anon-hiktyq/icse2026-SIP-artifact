#if !defined(__NUMUSEARRAY_H__)
#define __NUMUSEARRAY_H__

#include "common.h"
#include arraykeyisempty.h

#ifndef _MAXABITS_
	#define MAXABITS cast_int(sizeof(int) * CHAR_BIT - 1)
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


void numusearrayFun(void *p);

typedef struct __numusearray
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const Table*			t;
	/* Output Variables */
	/* In&Output Variables */
	Counters*			ct;
	/* Statement Variables*/
	/* Argument Variables */
} numusearray;

#endif // __NUMUSEARRAY_H__