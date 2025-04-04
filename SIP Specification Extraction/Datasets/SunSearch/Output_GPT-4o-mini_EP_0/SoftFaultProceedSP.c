
#include "SwitchSS.h"
#include "SoftFaultProceedSP.h"

/*@ 
  requires \valid(pIp);
  requires \valid(&pIp->mFWarning);
  requires \valid(pIp->mController + (0..2));
  assigns pIp->mFWarning.countSPset;
  assigns pIp->mFWarning.CWsp;
  assigns pIp->mFWarning.CWtf;
  assigns pIp->mFWarning.countSPset;
  assigns pIp->mFWarning.Wsp;
  assigns pIp->mController[0].Up;
  assigns pIp->mController[1].Up;
  assigns pIp->mController[2].Up;
  assigns pIp->countMode;
  assigns pIp->countPublic;
*/
void SoftFaultProceedSPFun(SoftFaultProceedSP *pIp)
{
    pIp->mFWarning.countSPset++;

    /*@
      loop invariant 0 <= pIp->mFWarning.countSPset <= 10;
      loop assigns pIp->mFWarning.countSPset;
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
