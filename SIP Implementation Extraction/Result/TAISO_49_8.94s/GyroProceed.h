#if !defined(__GYROPROCEED_H__)
#define __GYROPROCEED_H__

#include "common.h"
#include "GyroPick.h"
#include "GyroChoose.h"
#include "CalculateGyroRs.h"
#include "CalculateGyroDg.h"
#include "ModPNHP.h"

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


void GyroProceedFun(void *p);

typedef struct __GyroProceed
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	unint08			flgGryoCalc;
	SGyroData			mGyroData;
	/* Statement Variables*/
	/* Argument Variables */
	float32 			VG[9] [3];
} GyroProceed;

#endif // __GYROPROCEED_H__