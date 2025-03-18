
#include "SwitchSS.h"
#include "SoftFaultProceedSP.h"

/*@ 
  requires \valid(pIp);
  assigns pIp->mFWarning.countSPset, pIp->mFWarning.CWsp, pIp->mFWarning.CWtf, 
          pIp->mFWarning.Wsp, pIp->mController[0..2].Up, pIp->countMode, pIp->countPublic;
  ensures pIp->mFWarning.countSPset == \old(pIp->mFWarning.countSPset) + 1 || 
          (pIp->mFWarning.countSPset == 0 && \old(pIp->mFWarning.countSPset) == 10);
*/
void SoftFaultProceedSPFun(SoftFaultProceedSP *pIp)
{
    /*@ assert \valid(pIp); */
    pIp->mFWarning.countSPset++;

    /*@ loop invariant 0 <= pIp->mFWarning.countSPset <= 10;
        loop assigns pIp->mFWarning.countSPset, pIp->mFWarning.CWsp, pIp->mFWarning.CWtf, 
                     pIp->mFWarning.Wsp, pIp->mController[0..2].Up, pIp->countMode, pIp->countPublic;
        loop variant 10 - pIp->mFWarning.countSPset;
    */
    switch (pIp->mFWarning.countSPset)
    {
        case 5:
            IPCREATE(SwitchSS, ipSwitchSS);
            IPCALL(ipSwitchSS);
            break;

        case 10:
            pIp->mFWarning.CWsp = FALSE;
            pIp->mFWarning.CWtf = FALSE;
            pIp->mFWarning.countSPset = 0;
            pIp->mFWarning.Wsp = FALSE;

            TR32_FLGMODE_VALUE(SAM_DAMP);
            TR32_BIAS_WXRO_VALUE(0.0f);
            TR32_BIAS_WYPI_VALUE(0.0f);
            pIp->mController[0].Up = 0.0f;
            pIp->mController[1].Up = 0.0f;
            pIp->mController[2].Up = 0.0f;

            pIp->countMode = 0;
            pIp->countPublic = 0;
            break;

        default:
            break;
    }

    return;
}
