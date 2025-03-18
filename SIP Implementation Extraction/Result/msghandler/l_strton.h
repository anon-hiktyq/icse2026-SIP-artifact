#if !defined(__L_STRTON_H__)
#define __L_STRTON_H__

#include "common.h"
#include luaO_str2num.h

#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _TSVALUE_
	#define tsvalue check_exp(ttisstring(o), gco2ts(val_(o).gc))
#endif

#ifndef _GETLSTR_
	#define getlstr (strisshr(ts) \
		? (cast_void((len) = cast_sizet((ts)->shrlen)), rawgetshrstr(ts)) \
		: (cast_void((len) = (ts)->u.lnglen), (ts)->contents))
#endif

#ifndef _CVT2NUM_
	#define cvt2num 0
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif

typedef signed char ls_byte;
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