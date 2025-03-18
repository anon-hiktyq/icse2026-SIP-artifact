#include "SwitchSS.h"
#include "SoftFaultProceedSP.h"
void SoftFaultProceedSPFun(void *p)
{
    SoftFaultProceedSP *pIp = (SoftFaultProceedSP*)p;

	pIp -> mFWarning.countSPset++ ;

    switch (pIp -> mFWarning.countSPset)
    {

	    case 5:

			IPCREATE(SwitchSS, ipSwitchSS);
			IPCALL(ipSwitchSS);

			break ;

		case 10:

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