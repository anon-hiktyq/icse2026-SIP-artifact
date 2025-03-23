#if !defined(__PSEUDORATEMODULATOR_H__)
#define __PSEUDORATEMODULATOR_H__

#include "common.h"


#ifndef _UNINT08_
	typedef unsigned char   unint08;
#endif

#ifndef _FLOAT32_
	typedef float           float32;
#endif

#ifndef _SFRATEMODULATOR_
	typedef struct TAG_FALSE_RATE_MODULATOR
	{
		
		float32 	u;						/* �����ź�,����������� */
		float32 	r;						/* �����ź� */
		unint08 	Yp;						/* ���巽����� */
		unint08 	Yn;						/* ���巽����� */
		                            	
	}SFratemodulator;
#endif


void PseudoRateModulatorFun(void *p);

typedef struct __PseudoRateModulator
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	float32			h1;
	/* Output Variables */
	/* In&Output Variables */
	SFratemodulator*			pModulator;
	/* Statement Variables*/
	/* Argument Variables */
} PseudoRateModulator;

#endif // __PSEUDORATEMODULATOR_H__