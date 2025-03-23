#if !defined(__L_STRTON_H__)
#define __L_STRTON_H__

#include "common.h"
#include "luaO_str2num.h"

#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
#endif

#ifndef _tsvalue_
#define _tsvalue_
	#define tsvalue check_exp(ttisstring(o), gco2ts(val_(o).gc))
#endif

#ifndef _getlstr_
#define _getlstr_
	#define getlstr (strisshr(ts) \
		? (cast_void((len) = cast_sizet((ts)->shrlen)), rawgetshrstr(ts)) \
		: (cast_void((len) = (ts)->u.lnglen), (ts)->contents))
#endif

#ifndef _cvt2num_
#define _cvt2num_
	#define cvt2num 0
#endif

#ifndef _lu_byte_
#define _lu_byte_
	typedef unsigned char lu_byte;
#endif

#ifndef _ls_byte_
#define _ls_byte_
	typedef signed char ls_byte;
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


void l_strtonFun(void *p);

typedef struct __l_strton
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	const TValue*			obj;
	TValue*			result;
	/* Statement Variables*/
	/* Argument Variables */
} l_strton;

#endif // __L_STRTON_H__