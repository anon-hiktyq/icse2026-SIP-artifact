#if !defined(__ARRAYKEYISEMPTY_H__)
#define __ARRAYKEYISEMPTY_H__

#include "common.h"

#define LUA_TNIL 0

#ifndef _TAGISEMPTY_
	#define tagisempty(tag) (novariant(tag) == NULL)
#endif

#ifndef _GETARRTAG_
	#define getArrTag(t,k) ((lu_byte*)((t)->array) + sizeof(unsigned) + (k))
#endif

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



typedef struct __arraykeyisempty
{
/* 接口函数 */
	void (*fun)( struct __arraykeyisempty *);
/* 输入端口 */
	const Table*			t;
	unsigned int			key;
	/* 输出端口 */
	int*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} arraykeyisempty;

void arraykeyisemptyFun(arraykeyisempty *pIp);
#endif // __ARRAYKEYISEMPTY_H__