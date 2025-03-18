
#include "SoftFaultProceedSP.h"
#include "NoctrlJudge.h"
#include "SoftFaultJudgeSP.h"
#include "FaultJudgeProceed.h"

/*@ 
  requires \valid(pIp);
  requires \valid(&(pIp->mFWarning));
  assigns \nothing;
  ensures ((pIp->mFWarning.CWsp == TRUE && pIp->mFWarning.Wsp == FALSE) ==> \true) &&
          ((pIp->mFWarning.CWsp == TRUE && pIp->mFWarning.Wsp == TRUE) ==> \true);
*/
void FaultJudgeProceedFun(FaultJudgeProceed *pIp)
{
    /*@ 
      requires \valid(&(pIp->mFWarning));
      assigns \nothing;
      ensures (pIp->mFWarning.CWsp == TRUE && pIp->mFWarning.Wsp == FALSE) ==> \true;
    */
	if ((pIp -> mFWarning.CWsp == TRUE) && (pIp -> mFWarning.Wsp == FALSE))
    {
        IPCREATE(SoftFaultJudgeSP, ipSoftFaultJudgeSP);
        IPCALL(ipSoftFaultJudgeSP);
    }

    /*@ 
      requires \valid(&(pIp->mFWarning));
      assigns \nothing;
      ensures (pIp->mFWarning.CWsp == TRUE && pIp->mFWarning.Wsp == TRUE) ==> \true;
    */
    if ((pIp -> mFWarning.CWsp == TRUE) && (pIp -> mFWarning.Wsp == TRUE))
    {
    	IPCREATE(SoftFaultProceedSP, ipSoftFaultProceedSP);
    	IPCALL(ipSoftFaultProceedSP);
    }

    /*@ 
      assigns \nothing;
      ensures \true;
    */
    IPCREATE(NoctrlJudge, ipNoctrlJudge);
    IPCALL(ipNoctrlJudge);

	return;
}
