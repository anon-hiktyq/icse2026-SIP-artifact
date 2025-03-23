#if !defined(__INITVAR_H__)
#define __INITVAR_H__

#include "common.h"


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

#ifndef _SGYRODATA_
	typedef struct TAG_DIGITAL_GYRO_DATA
	{
	
	    unint08		countPick[9];		 	/* ����ԭʼ���ݴ���ʱ,��Ұ������ */   
	    float32 	Gi[3];				 	/* ���ݽǶȻ��� */
	    float32 	wa[9];				 	/* ���ݽ��ٶ�ģ�� */
	    float32 	wal[9];				 	/* ���������ݽ��ٶ�ģ���� */
	 	unint08		JoinTotal;           	/* �μӶ��˵����ݸ��� */
	 	unint16 	gyroStatus0;		 	/* ����״̬�� */
	 	unint16 	gyroStatus1;		 	/* ����״̬�� */
	    float32 	W[3];				 	/* ��������Ľ��ٶ� */
	    unint08		SignFlag[9] ; 		 	/* �μӶ��˵�������� */    
		float32 	Rtemp[3][5];		 	/* ��������� */
		unint32		stateFlag[9];			/* ���ݼӵ�״̬ */
		
	} SGyroData;
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


void InitVarFun(void *p);

typedef struct __InitVar
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	unint08			countInt32ms;
	unint32			countSate;
	unint32			countPublic;
	unint32			countMode;
	unint16			flgPRSAM;
	unint08			flgGryoCalc;
	unint16			flg160INT;
	SGyroData			mGyroData;
	SFratemodulator 			mModulator[3];
	SThrDistribute			mThrDistribute;
	SFWarning			mFWarning;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} InitVar;

#endif // __INITVAR_H__