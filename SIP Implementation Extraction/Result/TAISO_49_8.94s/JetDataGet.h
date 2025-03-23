#if !defined(__JETDATAGET_H__)
#define __JETDATAGET_H__

#include "common.h"
#include "ThrABAutoChoose.h"

#ifndef _UNINT08_
	typedef unsigned char   unint08;
#endif

#ifndef _STHRDISTRIBUTE_
	typedef struct TAG_UPS_2MS
	{	
		unint16 flgABChoose;				/* ��������֧ѡ���־ */
	    unint08 wPulse;         			/* ���������������,32��2ms�ж�ʱ�����10N������ */
		unint08 stateFlag[2];				/* �������ӵ�״̬ stateFlag[0]���ݣ�stateFlag[1]���ݣ� ȡֵΪ1ʱ�ӵ磬0ʱ�ϵ�*/
	    
	} SThrDistribute;
#endif


void JetDataGetFun(void *p);

typedef struct __JetDataGet
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	SThrDistribute			mThrDistribute;
	/* Statement Variables*/
	/* Argument Variables */
} JetDataGet;

#endif // __JETDATAGET_H__