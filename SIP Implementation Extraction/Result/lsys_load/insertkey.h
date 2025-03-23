#if !defined(__INSERTKEY_H__)
#define __INSERTKEY_H__

#include "common.h"
#include "mainpositionTV.h"
#include "getfreepos.h"
#include "mainpositionfromnode.h"

#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
#endif

#ifndef _cast_
#define _cast_
	#define cast ((t)(exp))
#endif

#ifndef _cast_int_
#define _cast_int_
	#define cast_int cast(int, (i))
#endif

#ifndef _isabstkey_
#define _isabstkey_
	#define isabstkey checktag((v), LUA_VABSTKEY)
#endif

#ifndef _isempty_
#define _isempty_
	#define isempty ttisnil(v)
#endif

#ifndef _setempty_
#define _setempty_
	#define setempty settt_(v, LUA_VEMPTY)
#endif

#ifndef _setnodekey_
#define _setnodekey_
	#define setnodekey { Node *n_=(node); const TValue *io_=(obj); \
		  n_->u.key_val = io_->value_; n_->u.key_tt = io_->tt_; }
#endif

#ifndef _gval_
#define _gval_
	#define gval (&(n)->i_val)
#endif

#ifndef _gnext_
#define _gnext_
	#define gnext ((n)->u.next)
#endif

#ifndef _isdummy_
#define _isdummy_
	#define isdummy ((t)->flags & BITDUMMY)
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

#ifndef _Node_
#define _Node_
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