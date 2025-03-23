#if !defined(__MATRIXMULTI_H__)
#define __MATRIXMULTI_H__

#include "common.h"


#ifndef _UNINT08_
	typedef unsigned char   unint08;
#endif

#ifndef _FLOAT32_
	typedef float           float32;
#endif


void MatrixMultiFun(void *p);

typedef struct __MatrixMulti
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const float32*			multiplier;
	unint08			nrow;
	unint08			nrc;
	unint08			ncol;
	/* Output Variables */
	/* In&Output Variables */
	float32*			product;
	const float32*			faciend;
	/* Statement Variables*/
	/* Argument Variables */
} MatrixMulti;

#endif // __MATRIXMULTI_H__