#if !defined(__LUAH_HGETSHORTSTR_H__)
#define __LUAH_HGETSHORTSTR_H__

#include "common.h"


#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
#endif

#ifndef _strisshr_
#define _strisshr_
	#define strisshr ((ts)->shrlen >= 0)
#endif

#ifndef _keyisshrstr_
#define _keyisshrstr_
	#define keyisshrstr (keytt(node) == ctb(LUA_VSHRSTR))
#endif

#ifndef _keystrval_
#define _keystrval_
	#define keystrval (gco2ts(keyval(node).gc))
#endif

#ifndef _eqshrstr_
#define _eqshrstr_
	#define eqshrstr check_exp((a)->tt == LUA_VSHRSTR, (a) == (b))
#endif

#ifndef _gval_
#define _gval_
	#define gval (&(n)->i_val)
#endif

#ifndef _gnext_
#define _gnext_
	#define gnext ((n)->u.next)
#endif

#ifndef _hashstr_
#define _hashstr_
	#define hashstr hashpow2(t, (str)->hash)
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

#ifndef _GCObject_
#define _GCObject_
	struct GCObject {
	  CommonHeader;
	};
#endif

#ifndef _TString_
#define _TString_
	struct TString {
	  CommonHeader;
	  lu_byte extra;  /* reserved words for short strings; "has hash" for longs */
	  ls_byte shrlen;  /* length for short strings, negative for long strings */
	  unsigned int hash;
	  union {
	    size_t lnglen;  /* length for long strings */
	    struct TString *hnext;  /* linked list for hash table */
	  } u;
	  char *contents;  /* pointer to content in long strings */
	  lua_Alloc falloc;  /* deallocation function for external strings */
	  void *ud;  /* user data for external strings */
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


void luaH_HgetshortstrFun(void *p);

typedef struct __luaH_Hgetshortstr
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	Table*			t;
	TString*			key;
	/* Output Variables */
	const TValue *			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} luaH_Hgetshortstr;

#endif // __LUAH_HGETSHORTSTR_H__