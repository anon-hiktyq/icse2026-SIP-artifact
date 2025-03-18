#if !defined(__L_STRCMP_H__)
#define __L_STRCMP_H__

#include "common.h"


#ifndef _GETLSTR_
	#define getlstr (strisshr(ts) \
		? (cast_void((len) = cast_sizet((ts)->shrlen)), rawgetshrstr(ts)) \
		: (cast_void((len) = (ts)->u.lnglen), (ts)->contents))
#endif

typedef signed char ls_byte;
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

void l_strcmpFun(void *p);

typedef struct __l_strcmp
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const TString*			ts1;
	const TString*			ts2;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} l_strcmp;

#endif // __L_STRCMP_H__