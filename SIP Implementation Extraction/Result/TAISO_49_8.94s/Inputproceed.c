#include "Inputproceed.h"
void InputproceedFun(void *p) 
{
    Inputproceed *pIp = (Inputproceed*)p;

	unint08 flgSP ;											/* Ӳ�ڶ���SP��־ */
    unint08 flgModetmp ;									/* ģʽ�� */

    flgModetmp = TR32_FLGMODE() ;							/* ��ʽ�� */

	{IPCALL(GyroProceed,ipGyroProceed_0);};											/* �������ݴ��� */
	
	if ( flgModetmp == SAM_CRUISE )     					/* Ѳ����ʽ */
	{
		if ( pIp -> mDSSData.flgSP == 1 )   						/* ̫���ɼ� */
		{
        	pIp -> mAttitude.angle[0] = pIp -> mDSSData.royaw ;			/* ��������̫�� */
        	pIp -> mAttitude.angle[1] = pIp -> mDSSData.piyaw ;			/* ��������̫�� */

        	 												/* ��̫�������滻��ǰ����ֵ */
       		pIp -> mGyroData.Gi[0] = pIp -> mDSSData.royaw ;				/* ���������ݻ���  */
       		pIp -> mGyroData.Gi[1] = pIp -> mDSSData.piyaw ;				/* ���������ݻ���  */
		}
		else												/* ̫�����ɼ� */
		{
		    pIp -> mAttitude.angle[0] = pIp -> mGyroData.Gi[0] ;			/* �����������ݻ��� */
        	pIp -> mAttitude.angle[1] = pIp -> mGyroData.Gi[1] ;			/* �����������ݻ��� */
		}
	}

	else    /* ����ģʽ */
	{
		pIp -> mAttitude.angle[0] = 0.0f ;							/* ���������� */
    	pIp -> mAttitude.angle[1] = 0.0f ;							/* ���������� */
	}


	pIp -> mAttitude.rate[0] = pIp -> mGyroData.W[0] ;					/* �������ٶ�����������Ĺ������ٶ� */
    pIp -> mAttitude.rate[1] = pIp -> mGyroData.W[1] ;					/* �������ٶ�����������ĸ������ٶ� */
	pIp -> mAttitude.rate[2] = pIp -> mGyroData.W[2] ;					/* ƫ�����ٶ������������ƫ�����ٶ� */


	return ;
}