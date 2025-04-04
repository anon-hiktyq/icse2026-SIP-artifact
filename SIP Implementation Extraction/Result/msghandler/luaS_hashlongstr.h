#if !defined(__LUAS_HASHLONGSTR_H__)
#define __LUAS_HASHLONGSTR_H__

#include "common.h"
#include "luaS_hash.h"

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

#ifndef _lu_byte_
#define _lu_byte_
	typedef unsigned char lu_byte;
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


void luaS_hashlongstrFun(void *p);

typedef struct __luaS_hashlongstr
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	unsigned int*			ret;
	/* In&Output Variables */
	TString*			ts;
	/* Statement Variables*/
	/* Argument Variables */
} luaS_hashlongstr;

#endif // __LUAS_HASHLONGSTR_H__