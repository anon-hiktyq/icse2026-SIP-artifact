
#include "SoftFaultJudgeSP.h"

/*@ 
requires \valid(pIp);
requires \valid(&(pIp->mDSSData));
requires \valid(&(pIp->mFWarning));
assigns pIp->mFWarning.countSPLost, pIp->mFWarning.countSPSeen, pIp->mFWarning.Wsp, pIp->mFWarning.countSPset;
*/
void SoftFaultJudgeSPFun(SoftFaultJudgeSP *pIp)
{
    /*@ requires \valid(&(pIp->mDSSData.flgSP));
        requires \valid(&(pIp->mFWarning.countSPLost));
        requires \valid(&(pIp->mFWarning.countSPSeen));
        assigns pIp->mFWarning.countSPLost, pIp->mFWarning.countSPSeen;
    */
    if (pIp->mDSSData.flgSP == 0)
    {
        pIp->mFWarning.countSPLost++;
        pIp->mFWarning.countSPSeen = 0;
    }
    else
    {
        /*@ requires \valid(&(pIp->mFWarning.countSPLost));
            requires \valid(&(pIp->mFWarning.countSPSeen));
            assigns pIp->mFWarning.countSPSeen;
        */
        if (pIp->mFWarning.countSPLost != 0)
        {
            pIp->mFWarning.countSPSeen++;
        }

        /*@ requires \valid(&(pIp->mFWarning.countSPSeen));
            requires \valid(&(pIp->mFWarning.countSPLost));
            assigns pIp->mFWarning.countSPLost, pIp->mFWarning.countSPSeen;
        */
        if (pIp->mFWarning.countSPSeen > 2)
        {
            pIp->mFWarning.countSPLost = 0;
            pIp->mFWarning.countSPSeen = 0;
        }
    }

    /*@ requires \valid(&(pIp->mFWarning.countSPLost));
        requires \valid(&(pIp->mFWarning.Wsp));
        requires \valid(&(pIp->mFWarning.countSPset));
        assigns pIp->mFWarning.Wsp, pIp->mFWarning.countSPLost, pIp->mFWarning.countSPset;
    */
    if (pIp->mFWarning.countSPLost > 33750)
    {
        pIp->mFWarning.Wsp = TRUE;
        pIp->mFWarning.countSPLost = 0;
        pIp->mFWarning.countSPset = 0;
    }

    return;
}
