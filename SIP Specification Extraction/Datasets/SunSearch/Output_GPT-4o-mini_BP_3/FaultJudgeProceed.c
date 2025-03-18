
#include "SoftFaultProceedSP.h"
#include "NoctrlJudge.h"
#include "SoftFaultJudgeSP.h"
#include "FaultJudgeProceed.h"

/*@ 
  requires pIp != NULL; 
  requires \valid(pIp);
  ensures \result == 0; 
*/
void FaultJudgeProceedFun(FaultJudgeProceed *pIp)
{
    /*@
      loop invariant \valid(pIp);
      loop assigns \nothing;
    */
    if ((pIp -> mFWarning.CWsp == TRUE) && (pIp -> mFWarning.Wsp == FALSE))
    {
        /*@
          ensures \exists ipSoftFaultJudgeSP: SoftFaultJudgeSP*; 
          ensures ipSoftFaultJudgeSP != NULL; 
        */
        IPCREATE(SoftFaultJudgeSP, ipSoftFaultJudgeSP);
        IPCALL(ipSoftFaultJudgeSP);
    }

    /*@
      loop invariant \valid(pIp);
      loop assigns \nothing;
    */
    if ((pIp -> mFWarning.CWsp == TRUE) && (pIp -> mFWarning.Wsp == TRUE))
    {
        /*@
          ensures \exists ipSoftFaultProceedSP: SoftFaultProceedSP*; 
          ensures ipSoftFaultProceedSP != NULL; 
        */
        IPCREATE(SoftFaultProceedSP, ipSoftFaultProceedSP);
        IPCALL(ipSoftFaultProceedSP);
    }

    /*@
      ensures \exists ipNoctrlJudge: NoctrlJudge*; 
      ensures ipNoctrlJudge != NULL; 
    */
    IPCREATE(NoctrlJudge, ipNoctrlJudge);
    IPCALL(ipNoctrlJudge);

    return;
}
