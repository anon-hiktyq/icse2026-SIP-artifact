#if !defined(__HASHKEYISEMPTY_H__)
#define __HASHKEYISEMPTY_H__

#include "common.h"
#include "getintfromhash.h"

#ifndef _l_castU2S_
#define _l_castU2S_
	#define l_castU2S ((lua_Integer)(i))
#endif

#ifndef _isempty_
#define _isempty_
	#define isempty ttisnil(v)
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


void hashkeyisemptyFun(void *p);

typedef struct __hashkeyisempty
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	lua_Unsigned			key;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	Table*			t;
	/* Statement Variables*/
	/* Argument Variables */
} hashkeyisempty;

#endif // __HASHKEYISEMPTY_H__