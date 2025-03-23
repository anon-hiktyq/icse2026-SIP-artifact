#include "FaultJudgeProceed.h"
void FaultJudgeProceedFun(void *p) 
{
    FaultJudgeProceed *pIp = (FaultJudgeProceed*)p;

	if ((pIp -> mFWarning.CWsp == TRUE) && (pIp -> mFWarning.Wsp == FALSE))
    {

        {IPCALL(SoftFaultJudgeSP,ipSoftFaultJudgeSP_0);};							    /* ̫����ʧ�ж� */
    }

    if ((pIp -> mFWarning.CWsp == TRUE) && (pIp -> mFWarning.Wsp == TRUE))
    {
    	{IPCALL(SoftFaultProceedSP,ipSoftFaultProceedSP_0);};								/* ̫����ʧ���� */
    }

    {IPCALL(NoctrlJudge,ipNoctrlJudge_0);};											/* �����ж� */

	return ;
}