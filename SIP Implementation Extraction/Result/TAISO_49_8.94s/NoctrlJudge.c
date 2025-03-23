#include "NoctrlJudge.h"
void NoctrlJudgeFun(void *p) 
{
    NoctrlJudge *pIp = (NoctrlJudge*)p;


    float32 fabsmax ;

    /* ��̬���ٶ���һ������2��/�� */
    {float32 TripleFabsMax_ret_0;IPCALL(TripleFabsMax,ipTripleFabsMax_0,.fx1 = mAttitude.rate[0],.fy2 = mAttitude.rate[1],.fz3 = mAttitude.rate[2],.ret = &TripleFabsMax_ret_0);fabsmax = TripleFabsMax_ret_0;};

    if (fabsmax > 2.0f)
    {
        pIp -> mFWarning.countAV++;

        if (pIp -> mFWarning.countAV > 300)
        {
        	pIp -> mFWarning.Wav = TRUE ;

    	}
    }
	else if(pIp -> mFWarning.countAV > 0)
	{
		pIp -> mFWarning.countAV--;
	}
	else
	{
		pIp -> nouse = pIp -> nouse  ;
	}

	return ;
}