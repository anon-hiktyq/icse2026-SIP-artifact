#if !defined(__LIMITCTRLANGLEINPUT_H__)
#define __LIMITCTRLANGLEINPUT_H__

#include "common.h"
#include "LimitFloat32.h"

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


void LimitCtrlAngleInputFun(void *p);

typedef struct __LimitCtrlAngleInput
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
} LimitCtrlAngleInput;

#endif // __LIMITCTRLANGLEINPUT_H__