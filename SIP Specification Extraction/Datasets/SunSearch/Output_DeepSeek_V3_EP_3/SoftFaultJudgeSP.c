
#include "SoftFaultJudgeSP.h"

/*@ 
  requires \valid(pIp);
  assigns pIp->mFWarning.countSPLost, pIp->mFWarning.countSPSeen, pIp->mFWarning.Wsp, pIp->mFWarning.countSPset;
  ensures pIp->mFWarning.countSPLost == 0 || pIp->mFWarning.countSPLost == \old(pIp->mFWarning.countSPLost) + 1;
  ensures pIp->mFWarning.countSPSeen == 0 || pIp->mFWarning.countSPSeen == \old(pIp->mFWarning.countSPSeen) + 1;
  ensures pIp->mFWarning.Wsp == \old(pIp->mFWarning.Wsp) || pIp->mFWarning.Wsp == TRUE;
*/
void SoftFaultJudgeSPFun(SoftFaultJudgeSP *pIp)
{
    /*@ assert \valid(pIp); */

    if (pIp->mDSSData.flgSP == 0)
    {
        pIp->mFWarning.countSPLost++;
        pIp->mFWarning.countSPSeen = 0;
    }
    else
    {
        if (pIp->mFWarning.countSPLost != 0)
        {
            pIp->mFWarning.countSPSeen++;
        }

        if (pIp->mFWarning.countSPSeen > 2)
        {
            pIp->mFWarning.countSPLost = 0;
            pIp->mFWarning.countSPSeen = 0;
        }
    }

    if (pIp->mFWarning.countSPLost > 33750)
    {
        pIp->mFWarning.Wsp = TRUE;
        pIp->mFWarning.countSPLost = 0;
        pIp->mFWarning.countSPset = 0;
    }

    return;
}
