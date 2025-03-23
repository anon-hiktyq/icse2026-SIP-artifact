#if !defined(__MATRIXTRAN_H__)
#define __MATRIXTRAN_H__

#include "common.h"


#ifndef _UNINT08_
	typedef unsigned char   unint08;
#endif

#ifndef _FLOAT32_
	typedef float           float32;
#endif


void MatrixTranFun(void *p);

typedef struct __MatrixTran
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const float32*			mat;
	unint08			nrow;
	unint08			ncol;
	/* Output Variables */
	/* In&Output Variables */
	float32*			tran;
	/* Statement Variables*/
	/* Argument Variables */
} MatrixTran;

#endif // __MATRIXTRAN_H__