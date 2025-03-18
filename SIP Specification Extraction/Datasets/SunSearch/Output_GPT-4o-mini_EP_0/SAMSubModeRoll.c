
#include "SwitchSS.h"
#include "SAMSubModeRoll.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->pSDS);
  requires \valid(pIp->pCtrl + (0..2));
  ensures \result == \old(pIp->countPublic) + (pIp->pSDS->flgSP == 0x1 ? 1 : 0);
  assigns pIp->countPublic, pIp->flgMode, pIp->countMode, pIp->flgPRSAM, pIp->mFWarning;
*/
void SAMSubModeRollFun(SAMSubModeRoll *pIp)
{
    float32 tmproyaw;

    /*@ loop invariant 0 <= pIp->countPublic <= 16;
        loop assigns pIp->countPublic;
        loop variant 16 - pIp->countPublic;
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

    /*@ loop invariant 0 <= pIp->countMode;
        loop assigns pIp->countMode, pIp->flgMode, pIp->flgPRSAM, pIp->mFWarning;
        loop variant 6250 - pIp->countMode;
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
