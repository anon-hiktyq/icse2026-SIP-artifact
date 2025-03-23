#if !defined(__MODECONTROL_H__)
#define __MODECONTROL_H__

#include "common.h"
#include "SAMSubModeDamp.h"
#include "SAMSubModePitch.h"
#include "SAMSubModeRoll.h"
#include "SAMSubModeCruise.h"

#ifndef _SAM_DAMP_
	#define SAM_DAMP 0x00
#endif

#ifndef _SAM_PITCH_
	#define SAM_PITCH 0x11
#endif

#ifndef _SAM_ROLL_
	#define SAM_ROLL 0x22
#endif

#ifndef _SAM_CRUISE_
	#define SAM_CRUISE 0x33
#endif

#ifndef _TR32_FLGMODE_
	#define TR32_FLGMODE Tr32Uint08(FST_FLGMODE, SND_FLGMODE, TRD_FLGMODE)
#endif

#ifndef _TR32_FLGMODE_VALUE_
	#define TR32_FLGMODE_VALUE TR32_VALUE(FST_FLGMODE, SND_FLGMODE, TRD_FLGMODE, (x))
#endif

#ifndef _UNINT08_
	typedef unsigned char   unint08;
#endif

#ifndef _UNINT32_
	typedef unsigned long   unint32;
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

#ifndef _SDSSDATA_
	typedef struct TAG_DSS_DATA
	{	
		unint32     stateFlag_A;			/* ���ݼӵ� */
		unint32     stateFlag_B;			/* ���ݼӵ� */
		float32 	royaw;
		float32 	piyaw;
	    unint32     flgSP;					/* ̫���ɼ���־ */
	}SDSSData;
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


void ModeControlFun(void *p);

typedef struct __ModeControl
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	unint32			countPublic;
	SAttitude			mAttitude;
	SController 			mController[3];
	/* Output Variables */
	/* In&Output Variables */
	unint32			countMode;
	unint16			flgPRSAM;
	SFWarning			mFWarning;
	/* Statement Variables*/
	/* Argument Variables */
	unint08			Count160ms;
	SDSSData			mDSSData;
} ModeControl;

#endif // __MODECONTROL_H__