
#include "SAMSubModePitch.h"

/*@ 
  @ requires pIp != \null; 
  @ requires pIp->pSDS != \null; 
  @ requires pIp->pCtrl != \null;
  @ assigns pIp->countPublic, pIp->countMode, pIp->flgMode, pIp->pCtrl[0].Up, pIp->pCtrl[1].Up, pIp->pCtrl[2].Up;
  @ ensures \true; // Function does not return a value, so we use \true instead of \result
  @ behavior flag_set:
  @   assumes pIp->pSDS->flgSP == 1;
  @   ensures pIp->countPublic == \old(pIp->countPublic) + (fabs(pIp->pSDS->piyaw) > 1.0f ? 1 : 0);
  @   ensures (\forall int i; 0 <= i < 3 ==> pIp->pCtrl[i].Up == (fabs(pIp->pSDS->piyaw) > 1.0f && pIp->countPublic <= 16 ? 0.0f : \old(pIp->pCtrl[i].Up)));
  @   ensures (fabs(pIp->pSDS->piyaw) > 1.0f && pIp->countPublic > 16) ==> (pIp->flgMode == SAM_CRUISE && pIp->countMode == 0 && pIp->countPublic == 0);
  @ behavior count_mode_check:
  @   assumes pIp->countMode > 5625;
  @   ensures pIp->flgMode == SAM_ROLL && pIp->countMode == 0 && pIp->countPublic == 0;
  @*/
void SAMSubModePitchFun(SAMSubModePitch *pIp)
{
    float32 pirawtmp;

    if (pIp->pSDS->flgSP == 1)
    {
        pirawtmp = fabs(pIp->pSDS->piyaw);

        if (pirawtmp > 1.0f)
        {
            pIp->countPublic++;

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
