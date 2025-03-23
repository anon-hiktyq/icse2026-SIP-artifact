#if !defined(__CLEARKEY_H__)
#define __CLEARKEY_H__

#include "common.h"


#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
#endif

#ifndef _isempty_
#define _isempty_
	#define isempty ttisnil(v)
#endif

#ifndef _keyiscollectable_
#define _keyiscollectable_
	#define keyiscollectable (keytt(n) & BIT_ISCOLLECTABLE)
#endif

#ifndef _setdeadkey_
#define _setdeadkey_
	#define setdeadkey (keytt(node) = LUA_TDEADKEY)
#endif

#ifndef _gval_
#define _gval_
	#define gval (&(n)->i_val)
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


void clearkeyFun(void *p);

typedef struct __clearkey
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	Node*			n;
	/* Statement Variables*/
	/* Argument Variables */
} clearkey;

#endif // __CLEARKEY_H__