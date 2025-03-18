#if !defined(__LUAH_SIZE_H__)
#define __LUAH_SIZE_H__

#include "common.h"
#include concretesize.h
#include sizehash.h

#ifndef _CAST_
	#define cast ((t)(exp))
#endif

#ifndef _ISDUMMY_
	#define isdummy ((t)->flags & BITDUMMY)
#endif

#ifndef _LU_MEM_
	typedef size_t lu_mem;
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
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

void luaH_sizeFun(void *p);

typedef struct __luaH_size
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	Table*			t;
	/* 输出端口 */
	lu_mem			sz;
	lu_mem*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} luaH_size;

#endif // __LUAH_SIZE_H__