#if !defined(__NUMUSEARRAY_H__)
#define __NUMUSEARRAY_H__

#include "common.h"


#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif


#ifndef _GCOBJECT_
	typedef struct GCObject {
	  int data;
	  struct GCObject * next;
	}GCObject;
#endif

#ifndef _VALUE_
	typedef union Value {
	  struct GCObject *gc;    /* collectable objects */
	  void *p;         /* light userdata */
	  int f; /* light C functions */
	  int i;   /* integer numbers */
	  int n;    /* float numbers */
	  /* not used, but may avoid warnings for uninitialized value */
	  lu_byte ub;
	}Value;
#endif


#define MAXABITS 100

#ifndef _TABLE_
	typedef struct Table {
	  lu_byte flags;  /* 1<<p means tagmethod(p) is not present */
	  lu_byte lsizenode;  /* log2 of number of slots of 'node' array */
	  unsigned int asize;  /* number of slots in 'array' array */
	  Value *array;  /* array part */
	  struct Table *metatable;
	  GCObject *gclist;
	} Table;
#endif

#ifndef _COUNTERS_
	typedef struct Counters{
	  unsigned total;
	  unsigned na;
	  int deleted;
	  unsigned nums[100];
	}Counters;
#endif




typedef struct __numusearray
{
/* 接口函数 */
	void (*fun)( struct __numusearray *);
/* 输入端口 */
	const Table*			t;
	/* 输出端口 */
	/* 输入输出端口 */
	Counters*			ct;
	/* 状态变量 */
	/* 参数变量 */
} numusearray;

void numusearrayFun(numusearray *pIp);
#endif // __NUMUSEARRAY_H__