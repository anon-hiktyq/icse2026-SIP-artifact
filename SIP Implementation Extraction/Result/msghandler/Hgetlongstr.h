#if !defined(__HGETLONGSTR_H__)
#define __HGETLONGSTR_H__

#include "common.h"
#include "getgeneric.h"

#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
#endif

#ifndef _cast_
#define _cast_
	#define cast ((t)(exp))
#endif

#ifndef _strisshr_
#define _strisshr_
	#define strisshr ((ts)->shrlen >= 0)
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


void HgetlongstrFun(void *p);

typedef struct __Hgetlongstr
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
} Hgetlongstr;

#endif // __HGETLONGSTR_H__