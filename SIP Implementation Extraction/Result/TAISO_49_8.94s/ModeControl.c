#include "ModeControl.h"
void ModeControlFun(void *p) 
{
    ModeControl *pIp = (ModeControl*)p;

	unint32 flgModetmp1;

	flgModetmp1 = TR32_FLGMODE() ;						    /* ����������ʽ�� */

    pIp -> countMode++ ;											/* �������ڼ����ۼ� */

    if (flgModetmp1 == SAM_DAMP)							/* SAM��ģʽת������ */
    {
        {IPCALL(SAMSubModeDamp,ipSAMSubModeDamp_0,.rate = &mAttitude.rate[0],.max = 0.15f,.countPublic = pIp->countPublic,.countMode = pIp->countMode,.flgMode = SAM_DAMP);};			/* SAM�������᷽ʽ */
    }
    else if (flgModetmp1 == SAM_PITCH)
    {
        SAMSubModePitch(pIp -> &mDSSData, pIp -> countPublic, pIp -> countMode, SAM_PITCH, pIp -> &mController[0]) ;		/* SAM����������ʽ */
    }
    else if (flgModetmp1 == SAM_ROLL)
    {
        SAMSubModeRoll(pIp -> &mDSSData, pIp -> countPublic, pIp -> countMode, SAM_ROLL, pIp -> &mController[0]) ;			/* SAM����������ʽ */
    }
    else if (flgModetmp1 == SAM_CRUISE)
    {
        SAMSubModeCruise(pIp -> countMode, pIp -> Count160ms, pIp -> mFWarning) ;									/* SAMѲ����ʽ */
    }
    else
    {
    	TR32_FLGMODE_VALUE(SAM_DAMP) ;			            /* R534 ����ʽ�ֲ�Ϊ�涨��4�ַ�ʽ����Ĭ�Ͻ����������᷽ʽ */
    }

	return ;
}