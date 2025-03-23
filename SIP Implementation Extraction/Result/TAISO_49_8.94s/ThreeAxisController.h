#if !defined(__THREEAXISCONTROLLER_H__)
#define __THREEAXISCONTROLLER_H__

#include "common.h"
#include "LimitFloat32.h"
#include "PseudoRateModulator.h"
#include "ThrusterCtrlLogic.h"

#ifndef _FLOAT32_
	typedef float           float32;
#endif

#ifndef _SCONTROLLER_
	typedef struct TAG_CONTROLLERIN
	{
	    
	    float32 	Up;						/* ������� */
	    float32 	Ud;						/* ������� */
	    float32 	fy;						/* ��� */
	    
	}SController;
#endif

#ifndef _SCONTROLLERPARAM_
	typedef struct TAG_CONTROLLER_PARAM
	{
	    
	    float32 	Kp;             		/* PD���� */
	    float32 	Kd;             		/* PD���� */
	    float32 	h1;             		/* ����ֵ */
	    
	} SControllerParam;
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


void ThreeAxisControllerFun(void *p);

typedef struct __ThreeAxisController
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	SController 			mController[3];
	SFratemodulator 			mModulator[3];
	SThrDistribute			mThrDistribute;
	/* Statement Variables*/
	/* Argument Variables */
	SControllerParam 			CTRL_PARAM_SAM[3];
} ThreeAxisController;

#endif // __THREEAXISCONTROLLER_H__