#if !defined(__LIMITCTRLRATEINPUT_H__)
#define __LIMITCTRLRATEINPUT_H__

#include "common.h"
#include "Tr32Float.h"
#include "LimitFloat32.h"

#ifndef _TR32_BIAS_WXRO_
	#define TR32_BIAS_WXRO Tr32Float(FST_BIAS_WXRO, SND_BIAS_WXRO, TRD_BIAS_WXRO)
#endif

#ifndef _TR32_BIAS_WYPI_
	#define TR32_BIAS_WYPI Tr32Float(FST_BIAS_WYPI, SND_BIAS_WYPI, TRD_BIAS_WYPI)
#endif

#ifndef _FLOAT32_
	typedef float           float32;
#endif

#ifndef _SATTITUDE_
	typedef struct TAG_ATTITUDE_PARA     	
	{                                    	
		                                 	
		float32 	angle[3];			 	/* ������̬�� */
		float32 	rate[3]; 			 	/* ������ٶ� */
		                                 	
	}SAttitude;
#endif

#ifndef _SCONTROLLER_
	typedef struct TAG_CONTROLLERIN
	{
	    
	    float32 	Up;						/* ������� */
	    float32 	Ud;						/* ������� */
	    float32 	fy;						/* ��� */
	    
	}SController;
#endif


void LimitCtrlRateInputFun(void *p);

typedef struct __LimitCtrlRateInput
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const SAttitude*			pSA;
	const float32			max;
	/* Output Variables */
	/* In&Output Variables */
	SController*			pSCtrl;
	/* Statement Variables*/
	/* Argument Variables */
} LimitCtrlRateInput;

#endif // __LIMITCTRLRATEINPUT_H__