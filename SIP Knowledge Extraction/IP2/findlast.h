#if !defined(__FINDLAST_H__)
#define __FINDLAST_H__

#include "common.h"


#ifndef _GCOBJECT_
	struct GCObject {
	  CommonHeader;
	};
#endif


void findlastFun(void *p);

typedef struct __findlast
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	/* 输出端口 */
	GCObject **			ret;
	/* 输入输出端口 */
	GCObject**			p;
	/* 状态变量 */
	/* 参数变量 */
} findlast;

#endif // __FINDLAST_H__