#if !defined(__LUAH_HGETSHORTSTR_H__)
#define __LUAH_HGETSHORTSTR_H__

#include "common.h"


#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#define strisshr ((ts)->shrlen >= 0)
#ifndef _KEYISSHRSTR_
	#define keyisshrstr (keytt(node) == ctb(LUA_VSHRSTR))
#endif

#ifndef _KEYSTRVAL_
	#define keystrval (gco2ts(keyval(node).gc))
#endif

#ifndef _EQSHRSTR_
	#define eqshrstr check_exp((a)->tt == LUA_VSHRSTR, (a) == (b))
#endif

#ifndef _GVAL_
	#define gval (&(n)->i_val)
#endif

#ifndef _GNEXT_
	#define gnext ((n)->u.next)
#endif

#ifndef _HASHSTR_
	#define hashstr hashpow2(t, (str)->hash)
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
struct GCObject {
  CommonHeader;
};
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