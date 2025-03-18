
#include "SwitchSS.h"
#include "SAMSubModeRoll.h"

/*@ axiomatic Sum_array {
      logic integer sum(int* array, integer begin, integer end) reads array[begin .. (end-1)];
      axiom empty:
      \forall int* a, integer b, e; b >= e ==> sum(a,b,e) == 0;
      axiom range:
      \forall int* a, integer b, e; b < e ==> sum(a,b,e) == sum(a,b,e-1) + a[e-1];
   }
*/

/*@ requires \valid(pIp);
    requires \valid(pIp->pSDS);
    requires \valid(pIp->pCtrl + (0..2));
    assigns pIp->countPublic, pIp->flgMode, pIp->countMode, pIp->pCtrl[0..2].Up, 
            pIp->flgPRSAM, pIp->mFWarning.flgups, pIp->mFWarning.countUPSpc;
*/
void SAMSubModeRollFun(SAMSubModeRoll *pIp)
{
    float32 tmproyaw;

    /*@ requires \valid(pIp->pSDS);
        assigns tmproyaw;
    */
    if (pIp->pSDS->flgSP == 0x1)
    {
        tmproyaw = ABS(pIp->pSDS->royaw);

        /*@ assigns pIp->countPublic, pIp->flgMode, pIp->countMode, pIp->pCtrl[0..2].Up;
        */
        if (tmproyaw > 1.0f)
        {
            pIp->countPublic++;

            /*@ assigns pIp->flgMode, pIp->countMode, pIp->countPublic;
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

    /*@ assigns pIp->flgMode, pIp->countMode, pIp->countPublic, pIp->flgPRSAM, 
                pIp->mFWarning.flgups, pIp->mFWarning.countUPSpc;
    */
    if (pIp->countMode > 6250)
    {
        pIp->flgMode = SAM_PITCH;
        TR32_FLGMODE_VALUE(pIp->flgMode);
        TR32_BIAS_WXRO_VALUE(0.0f);
        TR32_BIAS_WYPI_VALUE(-0.5f);

        pIp->countMode = 0;
        pIp->countPublic = 0;

        /*@ assigns pIp->flgPRSAM;
        */
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
