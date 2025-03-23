#if !defined(__DELAY_H__)
#define __DELAY_H__

#include "common.h"


#ifndef _UNINT16_
	typedef unsigned int    unint16;
#endif


void DelayFun(void *p);

typedef struct __Delay
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	unint16			delaytime;
	/* Output Variables */
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} Delay;

#endif // __DELAY_H__