#if !defined(__CHECKCAL16_H__)
#define __CHECKCAL16_H__

#include "common.h"


#ifndef _UNINT08_
	typedef unsigned char   unint08;
#endif

#ifndef _UNINT16_
	typedef unsigned int    unint16;
#endif

#ifndef _UNINT32_
	typedef unsigned long   unint32;
#endif


void CheckCal16Fun(void *p);

typedef struct __CheckCal16
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
} CheckCal16;

#endif // __CHECKCAL16_H__