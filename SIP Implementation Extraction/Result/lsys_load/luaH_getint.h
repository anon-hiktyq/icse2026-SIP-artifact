#if !defined(__LUAH_GETINT_H__)
#define __LUAH_GETINT_H__

#include "common.h"
#include "finishnodeget.h"

#ifndef _TAGISEMPTY_
	#define tagisempty (novariant(tag) == LUA_TNIL)
#endif

#ifndef _GETARRTAG_
	#define getArrTag (cast(lu_byte*, (t)->array) + sizeof(unsigned) + (k))
#endif

#ifndef _FARR2VAL_
	#define farr2val ((res)->tt_ = tag, (res)->value_ = *getArrVal(h,(k)))
#endif

#ifndef _IKEYINARRAY_
	#define ikeyinarray checkrange(k, t->asize)
#endif

#ifndef _LUA_INTEGER_
	typedef LUA_INTEGER lua_Integer;
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

void luaH_getintFun(void *p);

typedef struct __luaH_getint
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	lua_Integer			key;
	/* Output Variables */
	lu_byte*			ret;
	/* In&Output Variables */
	Table*			t;
	TValue*			res;
	/* Statement Variables*/
	/* Argument Variables */
} luaH_getint;

#endif // __LUAH_GETINT_H__