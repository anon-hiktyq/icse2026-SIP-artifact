#if !defined(__COMPUTESIZES_H__)
#define __COMPUTESIZES_H__

#include "common.h"


#ifndef _ARRAYXHASH_
	#define arrayXhash (cast_sizet(na) <= cast_sizet(nh) * 3)
#endif

#ifndef _COUNTERS_
	struct {
	  unsigned total;
	  unsigned na;
	  int deleted;
	  unsigned nums[MAXABITS + 1];
	};
#endif


void computesizesFun(void *p);

typedef struct __computesizes
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	/* 输出端口 */
	unsigned int			optimal;
	unsigned int*			ret;
	/* 输入输出端口 */
	Counters*			ct;
	/* 状态变量 */
	/* 参数变量 */
} computesizes;

#endif // __COMPUTESIZES_H__