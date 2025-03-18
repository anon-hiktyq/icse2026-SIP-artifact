#if !defined(__EXCHANGEHASHPART_H__)
#define __EXCHANGEHASHPART_H__

#include "common.h"


#ifndef _CAST_BYTE_
	#define cast_byte cast(lu_byte, (i))
#endif

#ifndef _BITDUMMY_
	#define BITDUMMY (1 << 6)
#endif

#ifndef _NOTBITDUMMY_
	#define NOTBITDUMMY cast_byte(~BITDUMMY)
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
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

void exchangehashpartFun(void *p);

typedef struct __exchangehashpart
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	Table*			t1;
	Table*			t2;
	/* Statement Variables*/
	/* Argument Variables */
} exchangehashpart;

#endif // __EXCHANGEHASHPART_H__