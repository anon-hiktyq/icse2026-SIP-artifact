#if !defined(__GETFREEPOS_H__)
#define __GETFREEPOS_H__

#include "common.h"


#ifndef _keyisnil_
#define _keyisnil_
	#define keyisnil (keytt(node) == LUA_TNIL)
#endif

#ifndef _sizenode_
#define _sizenode_
	#define sizenode (twoto((t)->lsizenode))
#endif

#ifndef _gnode_
#define _gnode_
	#define gnode (&(t)->node[i])
#endif

#ifndef _haslastfree_
#define _haslastfree_
	#define haslastfree ((t)->lsizenode >= LIMFORLAST)
#endif

#ifndef _getlastfree_
#define _getlastfree_
	#define getlastfree ((cast(Limbox *, (t)->node) - 1)->lastfree)
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


void getfreeposFun(void *p);

typedef struct __getfreepos
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	Node *			ret;
	/* In&Output Variables */
	Table*			t;
	/* Statement Variables*/
	/* Argument Variables */
} getfreepos;

#endif // __GETFREEPOS_H__