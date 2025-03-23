#if !defined(__LUAS_EQLNGSTR_H__)
#define __LUAS_EQLNGSTR_H__

#include "common.h"


#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
#endif

#ifndef _LUA_VLNGSTR_
#define _LUA_VLNGSTR_
	#define LUA_VLNGSTR makevariant(LUA_TSTRING, 1)
#endif

#ifndef _getlngstr_
#define _getlngstr_
	#define getlngstr check_exp(!strisshr(ts), (ts)->contents)
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


void luaS_eqlngstrFun(void *p);

typedef struct __luaS_eqlngstr
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	TString*			a;
	TString*			b;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} luaS_eqlngstr;

#endif // __LUAS_EQLNGSTR_H__