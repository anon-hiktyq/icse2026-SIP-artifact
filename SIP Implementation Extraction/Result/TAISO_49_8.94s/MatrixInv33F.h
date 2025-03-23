#if !defined(__MATRIXINV33F_H__)
#define __MATRIXINV33F_H__

#include "common.h"


#ifndef _TRUE32_
	#define TRUE32 0x90
#endif

#ifndef _FALSE32_
	#define FALSE32 0x00
#endif

#ifndef _FLT32_ZERO_
	#define FLT32_ZERO 1.0E-6
#endif

#ifndef _UNINT08_
	typedef unsigned char   unint08;
#endif

#ifndef _SIINT08_
	typedef signed   char   siint08;
#endif

#ifndef _FLOAT32_
	typedef float           float32;
#endif


void MatrixInv33FFun(void *p);

typedef struct __MatrixInv33F
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const float32*			src;
	/* Output Variables */
	unint08			bAbleInv;
	unint08*			ret;
	/* In&Output Variables */
	float32*			inv;
	/* Statement Variables*/
	/* Argument Variables */
} MatrixInv33F;

#endif // __MATRIXINV33F_H__