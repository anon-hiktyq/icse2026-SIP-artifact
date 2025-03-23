#if !defined(__GETUARTDATA_H__)
#define __GETUARTDATA_H__

#include "common.h"


#ifndef _UNINT08_
	typedef unsigned char   unint08;
#endif

#ifndef _UNINT32_
	typedef unsigned long   unint32;
#endif


void GetUartDataFun(void *p);

typedef struct __GetUartData
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const unint32			len;
	const unint32			addr;
	/* Output Variables */
	unint32			bSucc;
	unint32*			ret;
	/* In&Output Variables */
	unint08*			data;
	/* Statement Variables*/
	/* Argument Variables */
} GetUartData;

#endif // __GETUARTDATA_H__