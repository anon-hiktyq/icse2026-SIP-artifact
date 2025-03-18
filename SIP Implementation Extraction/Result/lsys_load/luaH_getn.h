#if !defined(__LUAH_GETN_H__)
#define __LUAH_GETN_H__

#include "common.h"
#include "arraykeyisempty.h"
#include "newhint.h"
#include "hashkeyisempty.h"
#include "hash_search.h"

#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _ISDUMMY_
	#define isdummy ((t)->flags & BITDUMMY)
#endif

#ifndef _LENHINT_
	#define lenhint cast(unsigned*, (t)->array)
#endif

#ifndef _LUA_UNSIGNED_
	typedef LUA_UNSIGNED lua_Unsigned;
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

void luaH_getnFun(void *p);

typedef struct __luaH_getn
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	lua_Unsigned*			ret;
	/* In&Output Variables */
	Table*			t;
	/* Statement Variables*/
	/* Argument Variables */
} luaH_getn;

#endif // __LUAH_GETN_H__