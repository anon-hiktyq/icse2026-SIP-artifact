#if !defined(__COMPUTESIZES_H__)
#define __COMPUTESIZES_H__

#include "common.h"


#ifndef _ARRAYXHASH_
	#define arrayXhash(na,nh) (na <= nh * 3)
#endif

#ifndef _COUNTERS_
	typedef struct Counters{
	  unsigned total;
	  unsigned na;
	  int deleted;
	  unsigned nums[100];
	}Counters;
#endif



typedef struct __computesizes
{
/* 接口函数 */
	void (*fun)( struct __computesizes *);
/* 输入端口 */
	/* 输出端口 */
	unsigned int			optimal;
	unsigned int*			ret;
	/* 输入输出端口 */
	Counters*			ct;
	/* 状态变量 */
	/* 参数变量 */
} computesizes;

void computesizesFun(computesizes *pIp);
#endif // __COMPUTESIZES_H__