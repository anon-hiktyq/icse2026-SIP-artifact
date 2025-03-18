
#include "SwitchSS.h"
#include "SoftFaultProceedSP.h"

/* 
   @requires pIp != NULL; 
   @ensures \result == \nothing; 
   @assigns pIp->mFWarning.countSPset, pIp->mFWarning.CWsp, pIp->mFWarning.CWtf, 
            pIp->mFWarning.Wsp, pIp->mController[0].Up, pIp->mController[1].Up, 
            pIp->mController[2].Up, pIp->countMode, pIp->countPublic;
*/
void SoftFaultProceedSPFun(SoftFaultProceedSP *pIp)
{
    /* 
       @assert pIp->mFWarning.countSPset >= 0; 
       @assigns pIp->mFWarning.countSPset; 
       @ensures pIp->mFWarning.countSPset == \old(pIp->mFWarning.countSPset) + 1; 
    */
    pIp -> mFWarning.countSPset++ ;

    switch (pIp -> mFWarning.countSPset)
    {
        case 5:
            /* 
               @assert pIp->mFWarning.countSPset == 5; 
               @assigns \result; 
               @ensures \result != NULL; 
            */
            {
                SoftFaultProceedSP *ipSwitchSS; // Declare ipSwitchSS
                IPCREATE(SwitchSS, ipSwitchSS);
                IPCALL(ipSwitchSS);
            }
            break ;

        case 10:
            /* 
               @assert pIp->mFWarning.countSPset == 10; 
               @assigns pIp->mFWarning.CWsp, pIp->mFWarning.CWtf, 
                        pIp->mFWarning.countSPset, pIp->mFWarning.Wsp, 
                        pIp->mController[0].Up, pIp->mController[1].Up, 
                        pIp->mController[2].Up, pIp->countMode, 
                        pIp->countPublic; 
               @ensures pIp->mFWarning.CWsp == FALSE; 
               @ensures pIp->mFWarning.CWtf == FALSE; 
               @ensures pIp->mFWarning.countSPset == 0; 
               @ensures pIp->mFWarning.Wsp == FALSE; 
               @ensures pIp->mController[0].Up == 0.0f; 
               @ensures pIp->mController[1].Up == 0.0f; 
               @ensures pIp->mController[2].Up == 0.0f; 
               @ensures pIp->countMode == 0; 
               @ensures pIp->countPublic == 0; 
            */
            pIp -> mFWarning.CWsp = FALSE ;
            pIp -> mFWarning.CWtf = FALSE ;
            pIp -> mFWarning.countSPset = 0 ;
            pIp -> mFWarning.Wsp = FALSE ;

            TR32_FLGMODE_VALUE(SAM_DAMP) ;
            TR32_BIAS_WXRO_VALUE(0.0f) ;
            TR32_BIAS_WYPI_VALUE(0.0f) ;
            pIp -> mController[0].Up = 0.0f ;
            pIp -> mController[1].Up = 0.0f ;
            pIp -> mController[2].Up = 0.0f ;

            pIp -> countMode = 0 ;
            pIp -> countPublic = 0 ;
            break ;

        default:
            break ;
    }

    return ;
}
