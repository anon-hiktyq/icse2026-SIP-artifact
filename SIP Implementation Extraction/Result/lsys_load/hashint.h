#if !defined(__HASHINT_H__)
#define __HASHINT_H__

#include "common.h"


#ifndef _cast_int_
#define _cast_int_
	#define cast_int cast(int, (i))
#endif

#ifndef _cast_uint_
#define _cast_uint_
	#define cast_uint cast(unsigned int, (i))
#endif

#ifndef _l_castS2U_
#define _l_castS2U_
	#define l_castS2U ((lua_Unsigned)(i))
#endif

#ifndef _sizenode_
#define _sizenode_
	#define sizenode (twoto((t)->lsizenode))
#endif

#ifndef _gnode_
#define _gnode_
	#define gnode (&(t)->node[i])
#endif

#ifndef _hashmod_
#define _hashmod_
	#define hashmod (gnode(t, ((n) % ((sizenode(t)-1u)|1u))))
#endif

#ifndef _lua_Integer_
#define _lua_Integer_
	typedef LUA_INTEGER lua_Integer;
#endif

#ifndef _lua_Unsigned_
#define _lua_Unsigned_
	typedef LUA_UNSIGNED lua_Unsigned;
#endif

#ifndef _lu_byte_
#define _lu_byte_
	typedef unsigned char lu_byte;
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


void hashintFun(void *p);

typedef struct __hashint
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const Table*			t;
	lua_Integer			i;
	/* Output Variables */
	Node *			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} hashint;

#endif // __HASHINT_H__