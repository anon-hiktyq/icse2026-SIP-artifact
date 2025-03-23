#if !defined(__GYROCHOOSE_H__)
#define __GYROCHOOSE_H__

#include "common.h"


#ifndef _UNINT08_
	typedef unsigned char   unint08;
#endif

#ifndef _UNINT16_
	typedef unsigned int    unint16;
#endif

#ifndef _UNINT32_
	typedef unsigned long   unint32;
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


void GyroChooseFun(void *p);

typedef struct __GyroChoose
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	SGyroData*			pGyroData;
	/* Statement Variables*/
	/* Argument Variables */
} GyroChoose;

#endif // __GYROCHOOSE_H__