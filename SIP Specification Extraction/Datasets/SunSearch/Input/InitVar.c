#include "InitVar.h"
void InitVarFun(InitVar *pIp)
{

	pIp -> flg160INT = 0x3333 ;
	pIp -> flgPRSAM = 0x3333 ;

	pIp -> mGyroData.gyroStatus0 = 0 ;
	pIp -> mGyroData.gyroStatus1 = 0 ;

	pIp -> countSate    = 0 ;
	pIp -> countPublic  = 0 ;
	pIp -> countMode    = 0 ;
	pIp -> countInt32ms = 0 ;

	pIp -> mFWarning.countSPLost = 0 ;
	pIp -> mFWarning.countSPSeen = 0 ;
	pIp -> mFWarning.countSPset  = 0 ;
	pIp -> mFWarning.countUPSpc  = 0 ;

	TR32_FLGMODE_VALUE(SAM_DAMP) ;
	TR32_BIAS_WXRO_VALUE(0.0f) ;
	TR32_BIAS_WYPI_VALUE(0.0f) ;

	pIp -> mThrDistribute.wPulse = 0x0 ;

	pIp -> mModulator[0].r = 0.0f ;
	pIp -> mModulator[1].r = 0.0f ;
	pIp -> mModulator[2].r = 0.0f ;

	pIp -> flgGryoCalc = FALSE ;

	return;
}