
#include "SoftFaultJudgeSP.h"

/*@ 
  @ requires pIp != NULL; 
  @ assigns pIp->mFWarning.countSPLost, pIp->mFWarning.countSPSeen, pIp->mFWarning.Wsp, pIp->mFWarning.countSPset;
  @ ensures (pIp->mDSSData.flgSP == 0 ==> 
  @          (pIp->mFWarning.countSPLost == old(pIp->mFWarning.countSPLost) + 1) && 
  @          (pIp->mFWarning.countSPSeen == 0)) ||
  @         (pIp->mDSSData.flgSP != 0 ==> 
  @          (pIp->mFWarning.countSPLost == old(pIp->mFWarning.countSPLost) + (old(pIp->mFWarning.countSPLost) != 0 ? 0 : 1)) && 
  @          (pIp->mFWarning.countSPSeen == old(pIp->mFWarning.countSPSeen) + (old(pIp->mFWarning.countSPLost) != 0 ? 1 : 0)) &&
  @          (pIp->mFWarning.countSPLost <= 33750));
  @
  @ // The following conditions are now correctly formatted
  @ \if old(pIp->mFWarning.countSPSeen) > 2 
  @ \then (pIp->mFWarning.countSPLost == 0 && pIp->mFWarning.countSPSeen == 0);
  @
  @ \if old(pIp->mFWarning.countSPLost > 33750) 
  @ \then (pIp->mFWarning.Wsp == TRUE && pIp->mFWarning.countSPLost == 0 && pIp->mFWarning.countSPset == 0);
  @
  @*/
void SoftFaultJudgeSPFun(SoftFaultJudgeSP *pIp)
{
    if (pIp -> mDSSData.flgSP == 0)
    {
        pIp -> mFWarning.countSPLost++ ;
        pIp -> mFWarning.countSPSeen = 0 ;
    }
    else
    {
        if (pIp -> mFWarning.countSPLost != 0)
        {
            pIp -> mFWarning.countSPSeen++ ;
        }

        if (pIp -> mFWarning.countSPSeen > 2)
        {
            pIp -> mFWarning.countSPLost = 0 ;
            pIp -> mFWarning.countSPSeen = 0 ;
        }
    }

    if (pIp -> mFWarning.countSPLost > 33750)
    {
        pIp -> mFWarning.Wsp = TRUE ;
        pIp -> mFWarning.countSPLost = 0 ;
        pIp -> mFWarning.countSPset = 0 ;
    }

    return ;
}
