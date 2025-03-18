
#include "SoftFaultProceedSP.h"
#include "NoctrlJudge.h"
#include "SoftFaultJudgeSP.h"
#include "FaultJudgeProceed.h"

/*@ 
  requires \valid(pIp);
  assigns \nothing;
*/
void FaultJudgeProceedFun(FaultJudgeProceed *pIp)
{
    /*@ 
      requires \valid(&pIp->mFWarning);
      assigns \nothing;
    */
    if ((pIp -> mFWarning.CWsp == TRUE) && (pIp -> mFWarning.Wsp == FALSE))
    {
        /*@ 
          assigns \nothing;
        */
        IPCREATE(SoftFaultJudgeSP, ipSoftFaultJudgeSP);
        /*@ 
          assigns \nothing;
        */
        IPCALL(ipSoftFaultJudgeSP);
    }

    /*@ 
      requires \valid(&pIp->mFWarning);
      assigns \nothing;
    */
    if ((pIp -> mFWarning.CWsp == TRUE) && (pIp -> mFWarning.Wsp == TRUE))
    {
        /*@ 
          assigns \nothing;
        */
        IPCREATE(SoftFaultProceedSP, ipSoftFaultProceedSP);
        /*@ 
          assigns \nothing;
        */
        IPCALL(ipSoftFaultProceedSP);
    }

    /*@ 
      assigns \nothing;
    */
    IPCREATE(NoctrlJudge, ipNoctrlJudge);
    /*@ 
      assigns \nothing;
    */
    IPCALL(ipNoctrlJudge);

    return ;
}
