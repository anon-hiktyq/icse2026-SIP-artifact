#if !defined(__SIZEHASH_H__)
#define __SIZEHASH_H__

#include "common.h"


#ifndef _cast_sizet_
#define _cast_sizet_
	#define cast_sizet cast(size_t, (i))
#endif

#ifndef _sizenode_
#define _sizenode_
	#define sizenode (twoto((t)->lsizenode))
#endif

#ifndef _extraLastfree_
#define _extraLastfree_
	#define extraLastfree (haslastfree(t) ? sizeof(Limbox) : 0)
#endif

#ifndef _lu_byte_
#define _lu_byte_
	typedef unsigned char lu_byte;
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