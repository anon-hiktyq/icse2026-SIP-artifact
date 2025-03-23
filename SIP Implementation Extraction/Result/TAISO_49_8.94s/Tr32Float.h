#if !defined(__TR32FLOAT_H__)
#define __TR32FLOAT_H__

#include "common.h"


#ifndef _UNINT32_
	typedef unsigned long   unint32;
#endif

#ifndef _FLOAT32_
	typedef float           float32;
#endif

#ifndef _UDTCONVERT_
	typedef union TAG_DATA_TYPE_CONVERT
	{
	      
	    unint08 ui08[4];				 	/* ����������ת��Ϊ1��4�ֽ������� */  
	    float32 flt32;                   	
	    unint32 ui32;                    	
	                                     	
	} UDTConvert;
#endif


void Tr32FloatFun(void *p);

typedef struct __Tr32Float
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	float32*			pA;
	float32*			pB;
	float32*			pC;
	/* Output Variables */
	UDTConvert			ui2f;
	float32*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} Tr32Float;

#endif // __TR32FLOAT_H__