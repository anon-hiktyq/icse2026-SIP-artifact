#if !defined(__THRABAUTOCHOOSE_H__)
#define __THRABAUTOCHOOSE_H__

#include "common.h"


#ifndef _TBS_A_
	#define TBS_A 0x00
#endif

#ifndef _TBS_B_
	#define TBS_B 0x33
#endif

#ifndef _UNINT08_
	typedef unsigned char   unint08;
#endif

#ifndef _UNINT16_
	typedef unsigned int    unint16;
#endif

#ifndef _STHRDISTRIBUTE_
	typedef struct TAG_UPS_2MS
	{	
		unint16 flgABChoose;				/* ��������֧ѡ���־ */
	    unint08 wPulse;         			/* ���������������,32��2ms�ж�ʱ�����10N������ */
		unint08 stateFlag[2];				/* �������ӵ�״̬ stateFlag[0]���ݣ�stateFlag[1]���ݣ� ȡֵΪ1ʱ�ӵ磬0ʱ�ϵ�*/
	    
	} SThrDistribute;
#endif


void ThrABAutoChooseFun(void *p);

typedef struct __ThrABAutoChoose
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	SThrDistribute			mThrDistribute;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} ThrABAutoChoose;

#endif // __THRABAUTOCHOOSE_H__