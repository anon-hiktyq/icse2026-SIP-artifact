
#include "InitVar.h"

/*@ 
  requires \valid(pIp);
  ensures pIp->flg160INT == 0x3333;
  ensures pIp->flgPRSAM == 0x3333;
  ensures pIp->mGyroData.gyroStatus0 == 0;
  ensures pIp->mGyroData.gyroStatus1 == 0;
  ensures pIp->countSate == 0;
  ensures pIp->countPublic == 0;
  ensures pIp->countMode == 0;
  ensures pIp->countInt32ms == 0;
  ensures pIp->mFWarning.countSPLost == 0;
  ensures pIp->mFWarning.countSPSeen == 0;
  ensures pIp->mFWarning.countSPset == 0;
  ensures pIp->mFWarning.countUPSpc == 0;
  ensures pIp->mThrDistribute.wPulse == 0x0;
  ensures pIp->mModulator[0].r == 0.0f;
  ensures pIp->mModulator[1].r == 0.0f;
  ensures pIp->mModulator[2].r == 0.0f;
  ensures pIp->flgGryoCalc == FALSE;
  assigns pIp->flg160INT, pIp->flgPRSAM, pIp->mGyroData.gyroStatus0, 
          pIp->mGyroData.gyroStatus1, pIp->countSate, pIp->countPublic, 
          pIp->countMode, pIp->countInt32ms, pIp->mFWarning.countSPLost, 
          pIp->mFWarning.countSPSeen, pIp->mFWarning.countSPset, 
          pIp->mFWarning.countUPSpc, pIp->mThrDistribute.wPulse, 
          pIp->mModulator[0].r, pIp->mModulator[1].r, 
          pIp->mModulator[2].r, pIp->flgGryoCalc;
*/
void InitVarFun(InitVar *pIp)
{
    pIp -> flg160INT = 0x3333;
    pIp -> flgPRSAM = 0x3333;

    pIp -> mGyroData.gyroStatus0 = 0;
    pIp -> mGyroData.gyroStatus1 = 0;

    pIp -> countSate    = 0;
    pIp -> countPublic  = 0;
    pIp -> countMode    = 0;
    pIp -> countInt32ms = 0;

    pIp -> mFWarning.countSPLost = 0;
    pIp -> mFWarning.countSPSeen = 0;
    pIp -> mFWarning.countSPset  = 0;
    pIp -> mFWarning.countUPSpc  = 0;

    TR32_FLGMODE_VALUE(SAM_DAMP);
    TR32_BIAS_WXRO_VALUE(0.0f);
    TR32_BIAS_WYPI_VALUE(0.0f);

    pIp -> mThrDistribute.wPulse = 0x0;

    pIp -> mModulator[0].r = 0.0f;
    pIp -> mModulator[1].r = 0.0f;
    pIp -> mModulator[2].r = 0.0f;

    pIp -> flgGryoCalc = FALSE;

    return;
}
