#if !defined(__LUAT_GETTM_H__)
#define __LUAT_GETTM_H__

#include "common.h"
#include luaH_Hgetshortstr.h

#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _CAST_BYTE_
	#define cast_byte cast(lu_byte, (i))
#endif

#ifndef _NOTM_
	#define notm ttisnil(tm)
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif

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
#ifndef _TMS_
	enum {
	  TM_INDEX,
	  TM_NEWINDEX,
	  TM_GC,
	  TM_MODE,
	  TM_LEN,
	  TM_EQ,  /* last tag method with fast access */
	  TM_ADD,
	  TM_SUB,
	  TM_MUL,
	  TM_MOD,
	  TM_POW,
	  TM_DIV,
	  TM_IDIV,
	  TM_BAND,
	  TM_BOR,
	  TM_BXOR,
	  TM_SHL,
	  TM_SHR,
	  TM_UNM,
	  TM_BNOT,
	  TM_LT,
	  TM_LE,
	  TM_CONCAT,
	  TM_CALL,
	  TM_CLOSE,
	  TM_N		/* number of elements in the enum */
	};
#endif


void luaT_gettmFun(void *p);

typedef struct __luaT_gettm
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	TMS			event;
	/* 输出端口 */
	const TValue *			ret;
	/* 输入输出端口 */
	Table*			events;
	TString*			ename;
	/* 状态变量 */
	/* 参数变量 */
} luaT_gettm;

#endif // __LUAT_GETTM_H__