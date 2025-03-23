#if !defined(__NEWCHECKEDKEY_H__)
#define __NEWCHECKEDKEY_H__

#include "common.h"
#include "keyinarray.h"
#include "insertkey.h"

#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
#endif

#ifndef _cast_
#define _cast_
	#define cast ((t)(exp))
#endif

#ifndef _obj2arr_
#define _obj2arr_
	#define obj2arr (*getArrTag(h,(k)) = (val)->tt_, *getArrVal(h,(k)) = (val)->value_)
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


void newcheckedkeyFun(void *p);

typedef struct __newcheckedkey
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	Table*			t;
	const TValue*			key;
	TValue*			value;
	/* Statement Variables*/
	/* Argument Variables */
} newcheckedkey;

#endif // __NEWCHECKEDKEY_H__