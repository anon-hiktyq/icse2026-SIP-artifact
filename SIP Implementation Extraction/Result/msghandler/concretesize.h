#if !defined(__CONCRETESIZE_H__)
#define __CONCRETESIZE_H__

#include "common.h"




void concretesizeFun(void *p);

typedef struct __concretesize
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	unsigned int			size;
	/* Output Variables */
	size_t*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} concretesize;

#endif // __CONCRETESIZE_H__