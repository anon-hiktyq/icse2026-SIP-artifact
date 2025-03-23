#if !defined(__NOCTRLJUDGE_H__)
#define __NOCTRLJUDGE_H__

#include "common.h"
#include "TripleFabsMax.h"

#ifndef _UNINT08_
	typedef unsigned char   unint08;
#endif

#ifndef _UNINT16_
	typedef unsigned int    unint16;
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


void NoctrlJudgeFun(void *p);

typedef struct __NoctrlJudge
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	SAttitude			mAttitude;
	/* Output Variables */
	/* In&Output Variables */
	unint08			nouse;
	SFWarning			mFWarning;
	/* Statement Variables*/
	/* Argument Variables */
} NoctrlJudge;

#endif // __NOCTRLJUDGE_H__