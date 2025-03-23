#include "GyroChoose.h"
void GyroChooseFun(void *p) 
{
    GyroChoose *pIp = (GyroChoose*)p;

	unint08 i ;									      		/* ѭ������ʱ���� */

	/* ȷ���μӹ������ݵĸ��� */
	pIp -> pGyroData->JoinTotal = 0 ;								/* �μӶ��˵����ݸ������� */
	pIp -> pGyroData->gyroStatus0 = 0 ;

	for ( i=0 ; i<9 ; i++ )									/* 9�����ݽ����ж� */
	{
		if (pIp -> pGyroData->stateFlag[i] == TRUE)  				/* �������״̬���� */
		{
			pIp -> pGyroData->SignFlag[pIp -> pGyroData->JoinTotal] = i ;	/* ͳ�ƲμӶ��˵���������� */
			pIp -> pGyroData->JoinTotal++ ;							/* ͳ�ƲμӶ��˵����ݸ��� */
			pIp -> pGyroData->gyroStatus0 = pIp -> pGyroData->gyroStatus0 | (1 << i) ;
		}

	}

	return ;
}