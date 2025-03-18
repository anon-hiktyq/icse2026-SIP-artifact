
#include "SwitchSS.h"
#include "SAMSubModeRoll.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->pSDS);
  requires \valid(pIp->pCtrl + (0..2));
  assigns pIp->countPublic, pIp->flgMode, pIp->countMode, pIp->pCtrl[0].Up, pIp->pCtrl[1].Up, pIp->pCtrl[2].Up, pIp->flgPRSAM, pIp->mFWarning.flgups, pIp->mFWarning.countUPSpc;
  ensures pIp->countPublic == 0 || pIp->countPublic <= 17;
  ensures pIp->countMode == 0 || pIp->countMode <= 6251;
*/
void SAMSubModeRollFun(SAMSubModeRoll *pIp)
{
    float32 tmproyaw;

    /*@ 
      requires \valid(pIp->pSDS);
      assigns tmproyaw, pIp->countPublic, pIp->flgMode, pIp->countMode, pIp->pCtrl[0].Up, pIp->pCtrl[1].Up, pIp->pCtrl[2].Up;
      ensures pIp->countPublic == 0 || pIp->countPublic <= 17;
      ensures pIp->countMode == 0 || pIp->countMode <= 6251;
    */
    if (pIp->pSDS->flgSP == 0x1)
    {
        tmproyaw = ABS(pIp->pSDS->royaw);

        if (tmproyaw > 1.0f)
        {
            pIp->countPublic++;

            if (pIp->countPublic > 16)
            {
                pIp->flgMode = SAM_CRUISE;
                TR32_FLGMODE_VALUE(pIp->flgMode);
                TR32_BIAS_WXRO_VALUE(0.0f);
                pIp->countMode = 0;
                pIp->countPublic = 0;
            }
            else
            {
                pIp->pCtrl[0].Up = 0.0f;
                pIp->pCtrl[1].Up = 0.0f;
                pIp->pCtrl[2].Up = 0.0f;
            }
        }
    }
    else
    {
        pIp->countPublic = 0;
    }

    /*@ 
      requires \valid(pIp);
      assigns pIp->flgMode, pIp->countMode, pIp->countPublic, pIp->flgPRSAM, pIp->mFWarning.flgups, pIp->mFWarning.countUPSpc;
      ensures pIp->countMode == 0;
      ensures pIp->countPublic == 0;
      ensures pIp->flgMode == SAM_PITCH || pIp->flgMode == SAM_CRUISE;
    */
    if (pIp->countMode > 6250)
    {
        pIp->flgMode = SAM_PITCH;
        TR32_FLGMODE_VALUE(pIp->flgMode);
        TR32_BIAS_WXRO_VALUE(0.0f);
        TR32_BIAS_WYPI_VALUE(-0.5f);

        pIp->countMode = 0;
        pIp->countPublic = 0;

        if (pIp->flgPRSAM == 0x3333)
        {
            IPCREATE(SwitchSS, ipSwitchSS);
            IPCALL(ipSwitchSS);

            pIp->flgPRSAM = 0xCCCC;
        }
        else
        {
            pIp->flgPRSAM = 0x3333;

            pIp->mFWarning.flgups = TRUE;
            pIp->mFWarning.countUPSpc = 0;
        }
    }

    return;
}
