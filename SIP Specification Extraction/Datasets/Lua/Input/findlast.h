#if !defined(__FINDLAST_H__)
#define __FINDLAST_H__

#include "common.h"


#ifndef _GCOBJECT_
	typedef struct GCObject {
	  int data;
	  struct GCObject * next;
	} GCObject;
#endif



typedef struct __findlast
{
/* 接口函数 */
	void (*fun)( struct __findlast *);
/* 输入端口 */
	/* 输出端口 */
	GCObject **			ret;
	/* 输入输出端口 */
	GCObject**			p;
	/* 状态变量 */
	/* 参数变量 */
} findlast;

void findlastFun(findlast *pIp);
#endif // __FINDLAST_H__