#if !defined(__LIMITFLOAT32_H__)
#define __LIMITFLOAT32_H__

#include "common.h"


#ifndef _FLOAT32_
	typedef float           float32;
#endif


void LimitFloat32Fun(void *p);

typedef struct __LimitFloat32
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	float32			fin;
	float32			fbound;
	/* Output Variables */
	float32			fvalue;
	float32*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} LimitFloat32;

#endif // __LIMITFLOAT32_H__