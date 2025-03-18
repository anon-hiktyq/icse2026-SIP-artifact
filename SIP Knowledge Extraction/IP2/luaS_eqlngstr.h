#if !defined(__LUAS_EQLNGSTR_H__)
#define __LUAS_EQLNGSTR_H__

#include "common.h"


#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _LUA_VLNGSTR_
	#define LUA_VLNGSTR makevariant(LUA_TSTRING, 1)
#endif

#ifndef _GETLNGSTR_
	#define getlngstr check_exp(!strisshr(ts), (ts)->contents)
#endif

#ifndef _TSTRING_
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
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	TString*			a;
	TString*			b;
	/* 输出端口 */
	int*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} luaS_eqlngstr;

#endif // __LUAS_EQLNGSTR_H__