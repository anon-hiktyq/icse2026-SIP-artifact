#if !defined(__HGETSTR_H__)
#define __HGETSTR_H__

#include "common.h"
#include "luaH_Hgetshortstr.h"
#include "Hgetlongstr.h"

#ifndef _strisshr_
#define _strisshr_
	#define strisshr ((ts)->shrlen >= 0)
#endif

#ifndef _ls_byte_
#define _ls_byte_
	typedef signed char ls_byte;
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


void HgetstrFun(void *p);

typedef struct __Hgetstr
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	const TValue *			ret;
	/* In&Output Variables */
	Table*			t;
	TString*			key;
	/* Statement Variables*/
	/* Argument Variables */
} Hgetstr;

#endif // __HGETSTR_H__