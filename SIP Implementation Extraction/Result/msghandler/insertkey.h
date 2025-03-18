#if !defined(__INSERTKEY_H__)
#define __INSERTKEY_H__

#include "common.h"
#include mainpositionTV.h
#include getfreepos.h
#include mainpositionfromnode.h

#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _CAST_
	#define cast ((t)(exp))
#endif

#ifndef _CAST_INT_
	#define cast_int cast(int, (i))
#endif

#ifndef _ISABSTKEY_
	#define isabstkey checktag((v), LUA_VABSTKEY)
#endif

#ifndef _ISEMPTY_
	#define isempty ttisnil(v)
#endif

#ifndef _SETEMPTY_
	#define setempty settt_(v, LUA_VEMPTY)
#endif

#ifndef _SETNODEKEY_
	#define setnodekey { Node *n_=(node); const TValue *io_=(obj); \
		  n_->u.key_val = io_->value_; n_->u.key_tt = io_->tt_; }
#endif

#ifndef _GVAL_
	#define gval (&(n)->i_val)
#endif

#ifndef _GNEXT_
	#define gnext ((n)->u.next)
#endif

#ifndef _ISDUMMY_
	#define isdummy ((t)->flags & BITDUMMY)
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif

union Value {
  struct GCObject *gc;    /* collectable objects */
  void *p;         /* light userdata */
  lua_CFunction f; /* light C functions */
  lua_Integer i;   /* integer numbers */
  lua_Number n;    /* float numbers */
  /* not used, but may avoid warnings for uninitialized value */
  lu_byte ub;
};
struct TValue {
  TValuefields;
};
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

void insertkeyFun(void *p);

typedef struct __insertkey
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	Table*			t;
	const TValue*			key;
	TValue*			value;
	/* Statement Variables*/
	/* Argument Variables */
} insertkey;

#endif // __INSERTKEY_H__