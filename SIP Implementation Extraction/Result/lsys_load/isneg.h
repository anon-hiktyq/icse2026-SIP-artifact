#if !defined(__ISNEG_H__)
#define __ISNEG_H__

#include "common.h"




void isnegFun(void *p);

typedef struct __isneg
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	const char**			s;
	/* Statement Variables*/
	/* Argument Variables */
} isneg;

#endif // __ISNEG_H__