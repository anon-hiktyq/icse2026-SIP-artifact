#if !defined(__FILTERPC_H__)
#define __FILTERPC_H__

#include "common.h"




void filterpcFun(void *p);

typedef struct __filterpc
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			pc;
	int			jmptarget;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} filterpc;

#endif // __FILTERPC_H__