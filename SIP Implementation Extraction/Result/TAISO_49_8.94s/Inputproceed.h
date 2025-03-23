#if !defined(__INPUTPROCEED_H__)
#define __INPUTPROCEED_H__

#include "common.h"
#include "GyroProceed.h"

#ifndef _SAM_CRUISE_
	#define SAM_CRUISE 0x33
#endif

#ifndef _TR32_FLGMODE_
	#define TR32_FLGMODE Tr32Uint08(FST_FLGMODE, SND_FLGMODE, TRD_FLGMODE)
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


void InputproceedFun(void *p);

typedef struct __Inputproceed
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	unint08			flgGryoCalc;
	SAttitude			mAttitude;
	SGyroData			mGyroData;
	/* Statement Variables*/
	/* Argument Variables */
	float32 			VG[9] [3];
	SDSSData			mDSSData;
} Inputproceed;

#endif // __INPUTPROCEED_H__