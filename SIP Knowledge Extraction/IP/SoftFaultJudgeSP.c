
#include "SoftFaultJudgeSP.h"

void SoftFaultJudgeSPFun(void *p)

{
    SoftFaultJudgeSP *pIp = (SoftFaultJudgeSP*)p;

    if (pIp -> mDSSData.flgSP == 0)
    {
    	pIp -> mFWarning.countSPLost++ ;
    	pIp -> mFWarning.countSPSeen = 0 ;
    }
    else
    {

    	if (pIp -> mFWarning.countSPLost != 0)
  
    	{
    		pIp -> mFWarning.countSPSeen++ ;
    	}

    
    	if (pIp -> mFWarning.countSPSeen > 2)
    	
    	{
    		pIp -> mFWarning.countSPLost = 0 ;
    		pIp -> mFWarning.countSPSeen = 0 ;
    	}
   
    }

    if (pIp -> mFWarning.countSPLost > 33750)
    {
    	pIp -> mFWarning.Wsp = TRUE ;
    	pIp -> mFWarning.countSPLost = 0 ;
    	pIp -> mFWarning.countSPset = 0 ;
    }

    return ;
}
