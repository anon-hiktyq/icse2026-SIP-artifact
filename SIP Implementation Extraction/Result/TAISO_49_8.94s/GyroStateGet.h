#if !defined(__GYROSTATEGET_H__)
#define __GYROSTATEGET_H__

#include "common.h"
#include "SendUartData.h"
#include "Delay.h"
#include "GetUartData.h"

#ifndef _DIVIATION_TO_FLOAT_FOG_
	#define DIVIATION_TO_FLOAT_FOG DiviationToFloat((x), 0xFFF, 0x800, 9.765625e-4f)
#endif

#ifndef _UNINT08_
	typedef unsigned char   unint08;
#endif

#ifndef _UNINT16_
	typedef unsigned int    unint16;
#endif

#ifndef _UNINT32_
	typedef unsigned long   unint32;
#endif

#ifndef _FLOAT32_
	typedef float           float32;
#endif


void GyroStateGetFun(void *p);

typedef struct __GyroStateGet
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	unint32			NumGyro;
	/* Output Variables */
	/* In&Output Variables */
	unint32*			stateFlag;
	float32*			wa;
	/* Statement Variables*/
	/* Argument Variables */
} GyroStateGet;

#endif // __GYROSTATEGET_H__