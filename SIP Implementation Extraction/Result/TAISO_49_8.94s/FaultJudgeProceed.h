#if !defined(__FAULTJUDGEPROCEED_H__)
#define __FAULTJUDGEPROCEED_H__

#include "common.h"
#include "SoftFaultJudgeSP.h"
#include "SoftFaultProceedSP.h"
#include "NoctrlJudge.h"

#ifndef _UNINT08_
	typedef unsigned char   unint08;
#endif

#ifndef _SFWARNING_
	typedef struct TAG_FAULT_WARNING
	{
		unint08 CWsp;
		unint08 CWtf;
		
	    unint08 Wsp;                        /* ̫���������������ϱ��� */	
	    unint08 Wtf;                        /* ����Ƶ���������ϱ��� */
	    unint08 Wav;
	    
	    unint08 flgups;						/* UPS�л���־ */
	    unint08 flgModeChange;				/* ģʽ�л���־ */
	    
		unint16 countAV;
	    unint16 countSPLost;				/* ̫����ʧ������ */
	    unint16 countSPSeen;				/* ̫���ɼ������� */
	    unint16 countSPset;					/* �л�̫�������� */
	    unint16 countUPSpc;					/* �ڶ��������л�UPS�̿ؼ����� */
	     
	} SFWarning;
#endif


void FaultJudgeProceedFun(void *p);

typedef struct __FaultJudgeProceed
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	SAttitude			mAttitude;
	/* Output Variables */
	/* In&Output Variables */
	unint08			nouse;
	unint32			countPublic;
	unint32			countMode;
	SController 			mController[3];
	SFWarning			mFWarning;
	/* Statement Variables*/
	/* Argument Variables */
	SDSSData			mDSSData;
} FaultJudgeProceed;

#endif // __FAULTJUDGEPROCEED_H__