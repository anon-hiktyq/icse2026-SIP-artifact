#include "SoftFaultJudgeSP.h"
void SoftFaultJudgeSPFun(void *p) 
{
    SoftFaultJudgeSP *pIp = (SoftFaultJudgeSP*)p;
  

    if (pIp -> mDSSData.flgSP == 0)     							/* SP = 0 ̫�����ɼ�*/
    {
    	pIp -> mFWarning.countSPLost++ ;							/* ̫�����ɼ���������1 */
    	pIp -> mFWarning.countSPSeen = 0 ;							/* ̫����ʱ���ɼ�����������  */
    }
    else
    {
    	if (pIp -> mFWarning.countSPLost != 0)    					/* ̫��һ�β��ɼ� */
    	{
    		pIp -> mFWarning.countSPSeen++ ;						/* ̫����ʱ���ɼ��������Լ� */
    	}

    	if (pIp -> mFWarning.countSPSeen > 2)  					/* ̫���������β��ɼ� */
    	{
    		pIp -> mFWarning.countSPLost = 0 ;						/* ̫�����ɼ����������� */
    		pIp -> mFWarning.countSPSeen = 0 ;						/* ̫����ʱ���ɼ�����������  */
    	}
    }

    /* ̫����ʧ����33750���� */
    if (pIp -> mFWarning.countSPLost > 33750)
    {
    	pIp -> mFWarning.Wsp = TRUE ;
    	pIp -> mFWarning.countSPLost = 0 ;
    	pIp -> mFWarning.countSPset = 0 ;							/* ���л�̫�������� */
    }

    return ;
}