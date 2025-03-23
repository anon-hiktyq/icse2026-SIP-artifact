#if !defined(__COMPUTESIZES_H__)
#define __COMPUTESIZES_H__

#include "common.h"


#ifndef _arrayXhash_
#define _arrayXhash_
	#define arrayXhash (cast_sizet(na) <= cast_sizet(nh) * 3)
#endif

#ifndef _Counters_
#define _Counters_
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
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	unsigned int*			ret;
	/* In&Output Variables */
	Counters*			ct;
	/* Statement Variables*/
	/* Argument Variables */
} computesizes;

#endif // __COMPUTESIZES_H__