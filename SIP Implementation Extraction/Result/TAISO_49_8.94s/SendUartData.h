#if !defined(__SENDUARTDATA_H__)
#define __SENDUARTDATA_H__

#include "common.h"


#ifndef _UNINT08_
	typedef unsigned char   unint08;
#endif

#ifndef _UNINT32_
	typedef unsigned long   unint32;
#endif


void SendUartDataFun(void *p);

typedef struct __SendUartData
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const unint08*			data;
	const unint32			len;
	const unint32			addr;
	/* Output Variables */
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} SendUartData;

#endif // __SENDUARTDATA_H__