#if !defined(__SAMSUBMODECRUISE_H__)
#define __SAMSUBMODECRUISE_H__

#include "common.h"


#ifndef _UNINT08_
	typedef unsigned char   unint08;
#endif

#ifndef _UNINT32_
	typedef unsigned long   unint32;
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


void SAMSubModeCruiseFun(void *p);

typedef struct __SAMSubModeCruise
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const unint32			countMode;
	/* Output Variables */
	SFWarning			mFWarning;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} SAMSubModeCruise;

#endif // __SAMSUBMODECRUISE_H__