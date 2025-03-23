#if !defined(__KEYINARRAY_H__)
#define __KEYINARRAY_H__

#include "common.h"


#ifndef _ttisinteger_
#define _ttisinteger_
	#define ttisinteger checktag((o), LUA_VNUMINT)
#endif

#ifndef _ivalue_
#define _ivalue_
	#define ivalue check_exp(ttisinteger(o), val_(o).i)
#endif

#ifndef _ikeyinarray_
#define _ikeyinarray_
	#define ikeyinarray checkrange(k, t->asize)
#endif

#ifndef _lua_Integer_
#define _lua_Integer_
	typedef LUA_INTEGER lua_Integer;
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


void keyinarrayFun(void *p);

typedef struct __keyinarray
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	Table*			t;
	const TValue*			key;
	/* Output Variables */
	unsigned int*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} keyinarray;

#endif // __KEYINARRAY_H__