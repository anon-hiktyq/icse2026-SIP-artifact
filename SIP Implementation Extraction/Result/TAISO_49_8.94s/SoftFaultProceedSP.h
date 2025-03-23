#if !defined(__SOFTFAULTPROCEEDSP_H__)
#define __SOFTFAULTPROCEEDSP_H__

#include "common.h"
#include "SwitchSS.h"

#ifndef _SAM_DAMP_
	#define SAM_DAMP 0x00
#endif

#ifndef _TR32_FLGMODE_VALUE_
	#define TR32_FLGMODE_VALUE TR32_VALUE(FST_FLGMODE, SND_FLGMODE, TRD_FLGMODE, (x))
#endif

#ifndef _TR32_BIAS_WXRO_VALUE_
	#define TR32_BIAS_WXRO_VALUE TR32_VALUE(FST_BIAS_WXRO, SND_BIAS_WXRO, TRD_BIAS_WXRO, (x))
#endif

#ifndef _TR32_BIAS_WYPI_VALUE_
	#define TR32_BIAS_WYPI_VALUE TR32_VALUE(FST_BIAS_WYPI, SND_BIAS_WYPI, TRD_BIAS_WYPI, (x))
#endif

#ifndef _UNINT08_
	typedef unsigned char   unint08;
#endif

#ifndef _UNINT16_
	typedef unsigned int    unint16;
#endif

#ifndef _UNINT32_
	typedef unsigned long   unint32;
#endif

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


void SoftFaultProceedSPFun(void *p);

typedef struct __SoftFaultProceedSP
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	SFWarning			mFWarning;
	/* In&Output Variables */
	unint32			countPublic;
	unint32			countMode;
	SController 			mController[3];
	/* Statement Variables*/
	/* Argument Variables */
	SDSSData			mDSSData;
} SoftFaultProceedSP;

#endif // __SOFTFAULTPROCEEDSP_H__