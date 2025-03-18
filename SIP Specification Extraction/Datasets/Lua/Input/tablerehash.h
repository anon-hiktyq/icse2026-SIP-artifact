#if !defined(__TABLEREHASH_H__)
#define __TABLEREHASH_H__

#include "common.h"


#ifndef _LMOD_
	#define lmod(size,s) (check_exp((size&(size-1))==0, (cast_uint(s) & cast_uint((size)-1))))
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif


#ifndef _TSTRING_
	typedef struct TString {
	  lu_byte extra;  /* reserved words for short strings; "has hash" for longs */
	  lu_byte shrlen;  /* length for short strings, negative for long strings */
	  unsigned int hash;
	  union {
	    size_t lnglen;  /* length for long strings */
	    struct TString *hnext;  /* linked list for hash table */
	  } u;
	  char *contents;  /* pointer to content in long strings */
	  void *ud;  /* user data for external strings */
	}TString;
#endif




typedef struct __tablerehash
{
/* 接口函数 */
	void (*fun)( struct __tablerehash *);
/* 输入端口 */
	int			osize;
	int			nsize;
	/* 输出端口 */
	/* 输入输出端口 */
	TString**			vect;
	/* 状态变量 */
	/* 参数变量 */
} tablerehash;

void tablerehashFun( tablerehash * pIp);

#endif // __TABLEREHASH_H__