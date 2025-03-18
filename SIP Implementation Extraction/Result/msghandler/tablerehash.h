#if !defined(__TABLEREHASH_H__)
#define __TABLEREHASH_H__

#include "common.h"


#ifndef _LMOD_
	#define lmod (check_exp((size&(size-1))==0, (cast_uint(s) & cast_uint((size)-1))))
#endif

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

void tablerehashFun(void *p);

typedef struct __tablerehash
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			osize;
	int			nsize;
	/* Output Variables */
	/* In&Output Variables */
	TString**			vect;
	/* Statement Variables*/
	/* Argument Variables */
} tablerehash;

#endif // __TABLEREHASH_H__