
#include "TripleFabsMax.h"
#include "NoctrlJudge.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->mAttitude.rate + (0..2));
  requires \valid(&(pIp->mFWarning.countAV));
  requires \valid(&(pIp->mFWarning.Wav));
  ensures \result == \old(pIp->mFWarning.countAV) + 1 || \result == \old(pIp->mFWarning.countAV) - 1 || \result == \old(pIp->mFWarning.countAV);
  assigns pIp->mFWarning.countAV, pIp->mFWarning.Wav, pIp->nouse;
*/
void NoctrlJudgeFun(NoctrlJudge *pIp)
{
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
            pIp -> mFWarning.Wav = TRUE;
        }
    }
    else if(pIp -> mFWarning.countAV > 0)
    {
        pIp -> mFWarning.countAV--;
    }
    else
    {
        pIp -> nouse = pIp -> nouse;
    }

    return;
}
