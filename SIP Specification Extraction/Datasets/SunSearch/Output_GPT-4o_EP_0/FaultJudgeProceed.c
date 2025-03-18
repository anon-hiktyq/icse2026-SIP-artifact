
#include "SoftFaultProceedSP.h"
#include "NoctrlJudge.h"
#include "SoftFaultJudgeSP.h"
#include "FaultJudgeProceed.h"

/*@ 
  requires \valid(pIp);
  requires \valid(&(pIp->mFWarning));
  assigns *pIp;
*/
void FaultJudgeProceedFun(FaultJudgeProceed *pIp)
{
    /*@ 
      loop invariant \valid(pIp);
      loop invariant \valid(&(pIp->mFWarning));
      loop assigns *pIp;
    */
    if ((pIp->mFWarning.CWsp == TRUE) && (pIp->mFWarning.Wsp == FALSE))
    {
        IPCREATE(SoftFaultJudgeSP, ipSoftFaultJudgeSP);
        IPCALL(ipSoftFaultJudgeSP);
    }

    if ((pIp->mFWarning.CWsp == TRUE) && (pIp->mFWarning.Wsp == TRUE))
    {
        IPCREATE(SoftFaultProceedSP, ipSoftFaultProceedSP);
        IPCALL(ipSoftFaultProceedSP);
    }

    IPCREATE(NoctrlJudge, ipNoctrlJudge);
    IPCALL(ipNoctrlJudge);

    return;
}
