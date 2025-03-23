#if !defined(__HASH_SEARCH_H__)
#define __HASH_SEARCH_H__

#include "common.h"
#include "hashkeyisempty.h"

#ifndef _LUA_MAXINTEGER_
#define _LUA_MAXINTEGER_
	#define LUA_MAXINTEGER _I64_MAX
#endif

#ifndef _l_castS2U_
#define _l_castS2U_
	#define l_castS2U ((lua_Unsigned)(i))
#endif

#ifndef _lua_Unsigned_
#define _lua_Unsigned_
	typedef LUA_UNSIGNED lua_Unsigned;
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


void hash_searchFun(void *p);

typedef struct __hash_search
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	lua_Unsigned			j;
	/* Output Variables */
	lua_Unsigned*			ret;
	/* In&Output Variables */
	Table*			t;
	/* Statement Variables*/
	/* Argument Variables */
} hash_search;

#endif // __HASH_SEARCH_H__