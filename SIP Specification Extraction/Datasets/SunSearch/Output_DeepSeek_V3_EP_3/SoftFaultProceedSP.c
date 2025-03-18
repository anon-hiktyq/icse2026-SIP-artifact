
#include "SwitchSS.h"
#include "SoftFaultProceedSP.h"

/*@ axiomatic SoftFaultProceedSP {
      logic integer countSPset(SoftFaultProceedSP *p) = p->mFWarning.countSPset;
      logic boolean CWsp(SoftFaultProceedSP *p) = p->mFWarning.CWsp;
      logic boolean CWtf(SoftFaultProceedSP *p) = p->mFWarning.CWtf;
      logic boolean Wsp(SoftFaultProceedSP *p) = p->mFWarning.Wsp;
      logic real Up(SoftFaultProceedSP *p, integer i) = p->mController[i].Up;
      logic integer countMode(SoftFaultProceedSP *p) = p->countMode;
      logic integer countPublic(SoftFaultProceedSP *p) = p->countPublic;
   }
*/

/*@ requires \valid(pIp);
    assigns pIp->mFWarning.countSPset, pIp->mFWarning.CWsp, pIp->mFWarning.CWtf,
            pIp->mFWarning.Wsp, pIp->mController[0..2].Up, pIp->countMode, pIp->countPublic;
    ensures countSPset(pIp) == \old(countSPset(pIp)) + 1;
    ensures countSPset(pIp) == 10 ==> 
            (CWsp(pIp) == FALSE && CWtf(pIp) == FALSE && Wsp(pIp) == FALSE &&
             Up(pIp, 0) == 0.0f && Up(pIp, 1) == 0.0f && Up(pIp, 2) == 0.0f &&
             countMode(pIp) == 0 && countPublic(pIp) == 0);
*/
void SoftFaultProceedSPFun(SoftFaultProceedSP *pIp)
{
    /*@ assert \valid(pIp); */
    pIp->mFWarning.countSPset++;

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
