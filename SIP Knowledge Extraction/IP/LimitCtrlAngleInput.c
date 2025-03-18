#include "LimitFloat32.h"
#include "LimitCtrlAngleInput.h"
void LimitCtrlAngleInputFun(void *p)
{
    LimitCtrlAngleInput *pIp = (LimitCtrlAngleInput*)p;

    pIp -> pSCtrl[0].Up = pIp -> pSA->angle[0] ;
    pIp -> pSCtrl[1].Up = pIp -> pSA->angle[1] ;
    pIp -> pSCtrl[2].Up = 0.0f ;

	float32 LimitFloat32_ret;
	IPCREATE(LimitFloat32, ipLimitFloat32, .fin = pIp->pSCtrl[0].Up, .fbound =  pIp->max, .ret = &(LimitFloat32_ret));
	IPCALL(ipLimitFloat32);

	pIp -> pSCtrl[0].Up = LimitFloat32_ret;

    float32 LimitFloat32_ret;
    IPCREATE(LimitFloat32, ipLimitFloat32, .fin = pIp->pSCtrl[1].Up, .fbound =  pIp->max, .ret = &(LimitFloat32_ret));
    IPCALL(ipLimitFloat32);

    pIp -> pSCtrl[1].Up = LimitFloat32_ret;

	return;
}