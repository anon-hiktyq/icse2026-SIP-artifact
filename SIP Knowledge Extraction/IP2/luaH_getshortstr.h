#if !defined(__LUAH_GETSHORTSTR_H__)
#define __LUAH_GETSHORTSTR_H__

#include "common.h"
#include finishnodeget.h

#ifndef _TVALUE_
	struct TValue {
	  TValuefields;
	};
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

void luaH_getshortstrFun(void *p);

typedef struct __luaH_getshortstr
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	/* 输出端口 */
	lu_byte*			ret;
	/* 输入输出端口 */
	Table*			t;
	TString*			key;
	TValue*			res;
	/* 状态变量 */
	/* 参数变量 */
} luaH_getshortstr;

#endif // __LUAH_GETSHORTSTR_H__