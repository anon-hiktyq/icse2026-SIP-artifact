#if !defined(__TCPROCESS_H__)
#define __TCPROCESS_H__

#include "common.h"
#include "GetUartData.h"
#include "B_TcProcess.h"

#ifndef _UNINT08_
	typedef unsigned char   unint08;
#endif

#ifndef _UNINT32_
	typedef unsigned long   unint32;
#endif


void TcProcessFun(void *p);

typedef struct __TcProcess
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} TcProcess;

#endif // __TCPROCESS_H__