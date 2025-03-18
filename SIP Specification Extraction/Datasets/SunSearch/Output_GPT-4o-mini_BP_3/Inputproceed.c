
#include "Tr32Uint08.h"
#include "GyroProceed.h"
#include "Inputproceed.h"

/*@
  requires pIp != \null;
  requires \valid(pIp->mDSSData);
  requires \valid(pIp->mAttitude);
  requires \valid(pIp->mGyroData);
  assigns pIp->mAttitude.angle[0], pIp->mAttitude.angle[1], 
          pIp->mGyroData.Gi[0], pIp->mGyroData.Gi[1],
          pIp->mAttitude.rate[0], pIp->mAttitude.rate[1], pIp->mAttitude.rate[2];
  ensures pIp->mAttitude.angle[0] == (flgModetmp == SAM_CRUISE && pIp->mDSSData.flgSP == 1 ? pIp->mDSSData.royaw : 0.0f);
  ensures pIp->mAttitude.angle[1] == (flgModetmp == SAM_CRUISE && pIp->mDSSData.flgSP == 1 ? pIp->mDSSData.piyaw : 0.0f);
  ensures pIp->mGyroData.Gi[0] == (flgModetmp == SAM_CRUISE && pIp->mDSSData.flgSP == 1 ? pIp->mDSSData.royaw : pIp->mGyroData.Gi[0]);
  ensures pIp->mGyroData.Gi[1] == (flgModetmp == SAM_CRUISE && pIp->mDSSData.flgSP == 1 ? pIp->mDSSData.piyaw : pIp->mGyroData.Gi[1]);
  ensures pIp->mAttitude.rate[0] == pIp->mGyroData.W[0];
  ensures pIp->mAttitude.rate[1] == pIp->mGyroData.W[1];
  ensures pIp->mAttitude.rate[2] == pIp->mGyroData.W[2];
*/
void InputproceedFun(Inputproceed *pIp)
{
	unint08 flgSP ;
    unint08 flgModetmp ;

    unint08 Tr32Uint08_ret;
    IPCREATE(Tr32Uint08, ipTr32Uint08, .pA = 0, .ret = &(Tr32Uint08_ret));
    IPCALL(ipTr32Uint08);
    flgModetmp = Tr32Uint08_ret;
	
	IPCREATE(GyroProceed, ipGyroProceed);
	IPCALL(ipGyroProceed);

	if ( flgModetmp == SAM_CRUISE )
	{
		if ( pIp -> mDSSData.flgSP == 1 )
		{
        	pIp -> mAttitude.angle[0] = pIp -> mDSSData.royaw ;
        	pIp -> mAttitude.angle[1] = pIp -> mDSSData.piyaw ;

       		pIp -> mGyroData.Gi[0] = pIp -> mDSSData.royaw ;
       		pIp -> mGyroData.Gi[1] = pIp -> mDSSData.piyaw ;
		}
		else
		{
		    pIp -> mAttitude.angle[0] = pIp -> mGyroData.Gi[0] ;
        	pIp -> mAttitude.angle[1] = pIp -> mGyroData.Gi[1] ;
		}
	}
	else
	{
		pIp -> mAttitude.angle[0] = 0.0f ;
    	pIp -> mAttitude.angle[1] = 0.0f ;
	}

	pIp -> mAttitude.rate[0] = pIp -> mGyroData.W[0] ;
    pIp -> mAttitude.rate[1] = pIp -> mGyroData.W[1] ;
	pIp -> mAttitude.rate[2] = pIp -> mGyroData.W[2] ;

	return ;
}
