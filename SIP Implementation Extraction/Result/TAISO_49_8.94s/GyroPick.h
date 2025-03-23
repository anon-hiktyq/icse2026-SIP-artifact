#if !defined(__GYROPICK_H__)
#define __GYROPICK_H__

#include "common.h"


#ifndef _ABS_
	#define ABS (((a) > 0) ? (a) : -(a))
#endif

#ifndef _UNINT08_
	typedef unsigned char   unint08;
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


void GyroPickFun(void *p);

typedef struct __GyroPick
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	SGyroData*			pGyroData;
	/* Statement Variables*/
	/* Argument Variables */
} GyroPick;

#endif // __GYROPICK_H__