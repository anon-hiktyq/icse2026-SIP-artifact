
#include "SAMSubModePitch.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->pSDS);
  requires \valid(pIp->pCtrl + (0..2));
  ensures \result == \old(pIp->countPublic);
  assigns pIp->countPublic, pIp->countMode, pIp->flgMode, pIp->pCtrl[0].Up, pIp->pCtrl[1].Up, pIp->pCtrl[2].Up;
*/
void SAMSubModePitchFun(SAMSubModePitch *pIp)
{
    float32 pirawtmp;

    /*@ loop invariant pIp->countPublic >= 0;
        loop assigns pIp->countPublic;
    */
    if (pIp->pSDS->flgSP == 1)
    {
        pirawtmp = fabs(pIp->pSDS->piyaw);

        /*@ loop invariant pirawtmp > 0.0f;
            loop assigns pIp->countPublic, pIp->flgMode, pIp->countMode, pIp->pCtrl[0].Up, pIp->pCtrl[1].Up, pIp->pCtrl[2].Up;
        */
        if (pirawtmp > 1.0f)
        {
            pIp->countPublic++;

            /*@ loop invariant pIp->countPublic <= 16;
                loop assigns pIp->countPublic, pIp->flgMode, pIp->countMode;
            */
            if (pIp->countPublic > 16)
            {
                TR32_BIAS_WYPI_VALUE(0.0f);

                pIp->flgMode = SAM_CRUISE;
                TR32_FLGMODE_VALUE(pIp->flgMode);
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

    /*@ loop invariant pIp->countMode >= 0;
        loop assigns pIp->flgMode, pIp->countMode, pIp->countPublic;
    */
    if (pIp->countMode > 5625)
    {
        pIp->flgMode = SAM_ROLL;
        TR32_FLGMODE_VALUE(pIp->flgMode);
        TR32_BIAS_WXRO_VALUE(0.5f);
        TR32_BIAS_WYPI_VALUE(0.0f);

        pIp->countMode = 0;
        pIp->countPublic = 0;
    }

    return;
}
