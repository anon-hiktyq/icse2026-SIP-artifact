
#include "SwitchSS.h"
#include "SAMSubModeRoll.h"

/*@ axiomatic ABS {
      logic real ABS(real x) = x >= 0.0 ? x : -x;
    }
*/

/*@ axiomatic ModeFlags {
      logic integer SAM_CRUISE = 0;
      logic integer SAM_PITCH = 1;
    }
*/

/*@ axiomatic BooleanValues {
      logic integer TRUE = 1;
      logic integer FALSE = 0;
    }
*/

/*@ requires \valid(pIp);
    requires \valid(pIp->pSDS);
    requires \valid(pIp->pCtrl + (0..2));
    requires \valid(&pIp->mFWarning);
    assigns pIp->countPublic, pIp->flgMode, pIp->countMode, pIp->pCtrl[0..2].Up, 
            pIp->flgPRSAM, pIp->mFWarning.flgups, pIp->mFWarning.countUPSpc;
    ensures pIp->flgMode == \old(pIp->flgMode) || pIp->flgMode == SAM_CRUISE || pIp->flgMode == SAM_PITCH;
*/
void SAMSubModeRollFun(SAMSubModeRoll *pIp)
{
    float32 tmproyaw;

    /*@ assert \valid(pIp->pSDS); */
    if (pIp->pSDS->flgSP == 0x1)
    {
        /*@ assert \valid(pIp->pSDS); */
        tmproyaw = ABS(pIp->pSDS->royaw);

        /*@ assert tmproyaw == ABS(\old(pIp->pSDS->royaw)); */
        if (tmproyaw > 1.0f)
        {
            pIp->countPublic++;

            /*@ loop invariant 0 <= pIp->countPublic <= 17;
                loop assigns pIp->countPublic, pIp->flgMode, pIp->countMode, pIp->pCtrl[0..2].Up;
                loop variant 17 - pIp->countPublic;
            */
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

    /*@ assert \valid(pIp); */
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
