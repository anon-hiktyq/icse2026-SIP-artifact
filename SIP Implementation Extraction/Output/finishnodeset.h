#if !defined(__FINISHNODESET_H__)
#define __FINISHNODESET_H__

#include "common.h"
#include "retpsetcode.h"

#ifndef _CAST_
	#define cast ((t)(exp))
#endif

#ifndef _SETOBJ_
	#define setobj { TValue *io1=(obj1); const TValue *io2=(obj2); \
	          io1->value_ = io2->value_; settt_(io1, io2->tt_); \
		  checkliveness(L,io1); lua_assert(!isnonstrictnil(io1)); }
#endif

#ifndef _TTISNIL_
	#define ttisnil checktype((v), LUA_TNIL)
#endif

#ifndef _HOK_
	#define HOK 0
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif

#ifndef _VALUE_
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

#ifndef _TVALUE_
	struct TValue {
	  TValuefields;
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

void finishnodesetFun(void *p);

typedef struct __finishnodeset
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	Table*			t;
	const TValue*			slot;
	TValue*			val;
	/* Statement Variables*/
	/* Argument Variables */
} finishnodeset;

#endif // __FINISHNODESET_H__