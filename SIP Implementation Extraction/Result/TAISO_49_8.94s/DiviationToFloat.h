#if !defined(__DIVIATIONTOFLOAT_H__)
#define __DIVIATIONTOFLOAT_H__

#include "common.h"


#ifndef _UNINT16_
	typedef unsigned int    unint16;
#endif

#ifndef _FLOAT32_
	typedef float           float32;
#endif


void DiviationToFloatFun(void *p);

typedef struct __DiviationToFloat
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	unint16			input;
	unint16			mask;
	unint16			offset;
	float32			LSB;
	/* Output Variables */
	float32			fresult;
	float32*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} DiviationToFloat;

#endif // __DIVIATIONTOFLOAT_H__