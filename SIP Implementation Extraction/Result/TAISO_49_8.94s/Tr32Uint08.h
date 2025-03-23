#if !defined(__TR32UINT08_H__)
#define __TR32UINT08_H__

#include "common.h"


#ifndef _UNINT08_
	typedef unsigned char   unint08;
#endif


void Tr32Uint08Fun(void *p);

typedef struct __Tr32Uint08
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	unint08*			pC;
	unint08*			pB;
	unint08*			pA;
	/* Output Variables */
	unint08			uiresult;
	unint08*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} Tr32Uint08;

#endif // __TR32UINT08_H__