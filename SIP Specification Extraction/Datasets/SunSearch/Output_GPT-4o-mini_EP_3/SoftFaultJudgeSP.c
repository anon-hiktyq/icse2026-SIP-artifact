
#include "SoftFaultJudgeSP.h"

/*@ 
  requires \valid(pIp);
  requires \valid(&pIp->mDSSData);
  requires \valid(&pIp->mFWarning);
  ensures \valid(&pIp->mFWarning);
*/
void SoftFaultJudgeSPFun(SoftFaultJudgeSP *pIp)
{
    /*@ loop assigns pIp->mFWarning.countSPLost, pIp->mFWarning.countSPSeen, pIp->mFWarning.Wsp, pIp->mFWarning.countSPset; */
    /*@ loop invariant pIp->mFWarning.countSPLost >= 0; */
    /*@ loop variant \old(pIp->mFWarning.countSPLost) - pIp->mFWarning.countSPLost; */
    
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
