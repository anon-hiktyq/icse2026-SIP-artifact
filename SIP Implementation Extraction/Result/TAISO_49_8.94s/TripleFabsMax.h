#if !defined(__TRIPLEFABSMAX_H__)
#define __TRIPLEFABSMAX_H__

#include "common.h"


#ifndef _FLOAT32_
	typedef float           float32;
#endif


void TripleFabsMaxFun(void *p);

typedef struct __TripleFabsMax
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	float32			fx1;
	float32			fy2;
	float32			fz3;
	/* Output Variables */
	float32			tmax;
	float32*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} TripleFabsMax;

#endif // __TRIPLEFABSMAX_H__