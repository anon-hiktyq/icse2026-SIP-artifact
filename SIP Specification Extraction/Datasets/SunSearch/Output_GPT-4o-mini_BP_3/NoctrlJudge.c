
#include "TripleFabsMax.h"
#include "NoctrlJudge.h"

/*@ 
  requires pIp != \null;
  assigns pIp->mFWarning.countAV, pIp->mFWarning.Wav, pIp->nouse;
  ensures pIp->mFWarning.countAV >= 0;
  ensures pIp->mFWarning.countAV <= 300;
*/
void NoctrlJudgeFun(NoctrlJudge *pIp)
{
    float32 fabsmax;
    float32 TripleFabsMax_ret;

    /*@
      assigns TripleFabsMax_ret;
      ensures TripleFabsMax_ret == \abs(pIp->mAttitude.rate[0]) + \abs(pIp->mAttitude.rate[1]) + \abs(pIp->mAttitude.rate[2]);
    */
    IPCREATE(TripleFabsMax, ipTripleFabsMax, .fx1 =  pIp->mAttitude.rate[0], .fy2 =  pIp->mAttitude.rate[1], .fz3 =  pIp->mAttitude.rate[2], .ret = &(TripleFabsMax_ret));
    IPCALL(ipTripleFabsMax);

    fabsmax = TripleFabsMax_ret;

    /*@
      ensures pIp->mFWarning.countAV >= 0;
      ensures pIp->mFWarning.countAV <= 300;
    */
    if (fabsmax > 2.0f)
    {
        pIp -> mFWarning.countAV = \min(pIp->mFWarning.countAV + 1, 300);

        /*@
          ensures pIp->mFWarning.countAV <= 300;
        */
        if (pIp -> mFWarning.countAV == 300)
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
