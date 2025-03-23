#if !defined(__LIMITCONTROLLERINPUT_H__)
#define __LIMITCONTROLLERINPUT_H__

#include "common.h"
#include "LimitCtrlAngleInput.h"
#include "LimitCtrlRateInput.h"

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


void LimitControllerInputFun(void *p);

typedef struct __LimitControllerInput
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} LimitControllerInput;

#endif // __LIMITCONTROLLERINPUT_H__