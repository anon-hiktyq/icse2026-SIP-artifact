#if !defined(__LUAH_GETSTR_H__)
#define __LUAH_GETSTR_H__

#include "common.h"
#include "finishnodeget.h"

#ifndef _TValue_
#define _TValue_
	struct TValue {
	  TValuefields;
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


void luaH_getstrFun(void *p);

typedef struct __luaH_getstr
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	lu_byte*			ret;
	/* In&Output Variables */
	Table*			t;
	TString*			key;
	TValue*			res;
	/* Statement Variables*/
	/* Argument Variables */
} luaH_getstr;

#endif // __LUAH_GETSTR_H__