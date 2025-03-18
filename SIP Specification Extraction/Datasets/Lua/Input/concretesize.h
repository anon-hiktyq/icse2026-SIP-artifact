#if !defined(__CONCRETESIZE_H__)
#define __CONCRETESIZE_H__

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
	  GCObject *gc;    /* collectable objects */
	  void *p;         /* light userdata */
	  int f; /* light C functions */
	  int i;   /* integer numbers */
	  int n;    /* float numbers */
	  /* not used, but may avoid warnings for uninitialized value */
	  lu_byte ub;
	} Value;
#endif

typedef struct __concretesize
{
/* 接口函数 */
	void (*fun)( struct __concretesize *);
/* 输入端口 */
	unsigned int			size;
	/* 输出端口 */
	size_t*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} concretesize;

void concretesizeFun(concretesize *pIp);
#endif // __CONCRETESIZE_H__