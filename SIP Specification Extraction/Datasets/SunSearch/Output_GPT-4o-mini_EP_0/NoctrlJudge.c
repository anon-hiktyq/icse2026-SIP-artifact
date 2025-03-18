
#include "TripleFabsMax.h"
#include "NoctrlJudge.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->mAttitude.rate + (0..2));
  assigns pIp->mFWarning.countAV, pIp->mFWarning.Wav;
  ensures \result == ;
*/
void NoctrlJudgeFun(NoctrlJudge *pIp)
{
    float32 fabsmax;
    float32 TripleFabsMax_ret;

    /*@ 
      requires \valid(&(TripleFabsMax_ret));
      assigns TripleFabsMax_ret;
    */
    IPCREATE(TripleFabsMax, ipTripleFabsMax, .fx1 =  pIp->mAttitude.rate[0], .fy2 =  pIp->mAttitude.rate[1], .fz3 =  pIp->mAttitude.rate[2], .ret = &(TripleFabsMax_ret));
    IPCALL(ipTripleFabsMax);

    fabsmax = TripleFabsMax_ret;

    /*@ loop invariant pIp->mFWarning.countAV >= 0;
        loop assigns pIp->mFWarning.countAV;
    */
    if (fabsmax > 2.0f)
    {
        pIp->mFWarning.countAV++;

        /*@ 
          requires pIp->mFWarning.countAV > 300;
          assigns pIp->mFWarning.Wav;
        */
        if (pIp->mFWarning.countAV > 300)
        {
            pIp->mFWarning.Wav = TRUE;
        }
    }
    else if (pIp->mFWarning.countAV > 0)
    {
        pIp->mFWarning.countAV--;
    }
    else
    {
        pIp->nouse = pIp->nouse; // No operation
    }

    return;
}
