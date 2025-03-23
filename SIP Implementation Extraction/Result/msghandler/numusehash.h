#if !defined(__NUMUSEHASH_H__)
#define __NUMUSEHASH_H__

#include "common.h"
#include "countint.h"

#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
#endif

#ifndef _isempty_
#define _isempty_
	#define isempty ttisnil(v)
#endif

#ifndef _keyisnil_
#define _keyisnil_
	#define keyisnil (keytt(node) == LUA_TNIL)
#endif

#ifndef _keyisinteger_
#define _keyisinteger_
	#define keyisinteger (keytt(node) == LUA_VNUMINT)
#endif

#ifndef _keyival_
#define _keyival_
	#define keyival (keyval(node).i)
#endif

#ifndef _sizenode_
#define _sizenode_
	#define sizenode (twoto((t)->lsizenode))
#endif

#ifndef _gval_
#define _gval_
	#define gval (&(n)->i_val)
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

#ifndef _Counters_
#define _Counters_
	struct {
	  unsigned total;
	  unsigned na;
	  int deleted;
	  unsigned nums[MAXABITS + 1];
	};
#endif


void numusehashFun(void *p);

typedef struct __numusehash
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const Table*			t;
	/* Output Variables */
	/* In&Output Variables */
	Counters*			ct;
	/* Statement Variables*/
	/* Argument Variables */
} numusehash;

#endif // __NUMUSEHASH_H__