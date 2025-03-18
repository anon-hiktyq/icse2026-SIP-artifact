#if !defined(__SIZEHASH_H__)
#define __SIZEHASH_H__

#include "common.h"


#ifndef _CAST_SIZET_
	#define cast_sizet cast(size_t, (i))
#endif

#ifndef _SIZENODE_
	#define sizenode (twoto((t)->lsizenode))
#endif

#ifndef _EXTRALASTFREE_
	#define extraLastfree (haslastfree(t) ? sizeof(Limbox) : 0)
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
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

void sizehashFun(void *p);

typedef struct __sizehash
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	Table*			t;
	/* Output Variables */
	size_t*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} sizehash;

#endif // __SIZEHASH_H__