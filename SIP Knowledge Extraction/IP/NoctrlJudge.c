#include "TripleFabsMax.h"
#include "NoctrlJudge.h"
void NoctrlJudgeFun(void *p)
{
    NoctrlJudge *pIp = (NoctrlJudge*)p;

    float32 fabsmax;
    float32 TripleFabsMax_ret;
    IPCREATE(TripleFabsMax, ipTripleFabsMax, .fx1 =  pIp->mAttitude.rate[0], .fy2 =  pIp->mAttitude.rate[1], .fz3 =  pIp->mAttitude.rate[2], .ret = &(TripleFabsMax_ret));
    IPCALL(ipTripleFabsMax);

    fabsmax = TripleFabsMax_ret;

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