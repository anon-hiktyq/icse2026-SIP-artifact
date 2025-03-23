#if !defined(__CHECKCAL_H__)
#define __CHECKCAL_H__

#include "common.h"


#ifndef _UNINT08_
	typedef unsigned char   unint08;
#endif

#ifndef _UNINT32_
	typedef unsigned long   unint32;
#endif


void CheckCalFun(void *p);

typedef struct __CheckCal
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const unint32			len;
	const unint08*			pkv;
	/* Output Variables */
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} CheckCal;

#endif // __CHECKCAL_H__