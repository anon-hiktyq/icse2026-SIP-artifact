#if !defined(__THRUSTERCTRLLOGIC_H__)
#define __THRUSTERCTRLLOGIC_H__

#include "common.h"


#ifndef _UNINT08_
	typedef unsigned char   unint08;
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

#ifndef _STHRDISTRIBUTE_
	typedef struct TAG_UPS_2MS
	{	
		unint16 flgABChoose;				/* ��������֧ѡ���־ */
	    unint08 wPulse;         			/* ���������������,32��2ms�ж�ʱ�����10N������ */
		unint08 stateFlag[2];				/* �������ӵ�״̬ stateFlag[0]���ݣ�stateFlag[1]���ݣ� ȡֵΪ1ʱ�ӵ磬0ʱ�ϵ�*/
	    
	} SThrDistribute;
#endif


void ThrusterCtrlLogicFun(void *p);

typedef struct __ThrusterCtrlLogic
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	SFratemodulator 			mModulator[3];
	/* Output Variables */
	/* In&Output Variables */
	SThrDistribute			mThrDistribute;
	/* Statement Variables*/
	/* Argument Variables */
} ThrusterCtrlLogic;

#endif // __THRUSTERCTRLLOGIC_H__