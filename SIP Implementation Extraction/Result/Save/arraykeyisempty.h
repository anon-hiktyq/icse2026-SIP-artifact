#if !defined(__ARRAYKEYISEMPTY_H__)
#define __ARRAYKEYISEMPTY_H__

#include "common.h"


#ifndef _tagisempty_
#define _tagisempty_
	#define tagisempty (novariant(tag) == LUA_TNIL)
#endif

#ifndef _getArrTag_
#define _getArrTag_
	#define getArrTag (cast(lu_byte*, (t)->array) + sizeof(unsigned) + (k))
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


void arraykeyisemptyFun(void *p);

typedef struct __arraykeyisempty
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const Table*			t;
	unsigned int			key;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} arraykeyisempty;

#endif // __ARRAYKEYISEMPTY_H__