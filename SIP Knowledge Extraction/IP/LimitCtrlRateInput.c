#include "LimitFloat32.h"
#include "Tr32Float.h"
#include "LimitCtrlRateInput.h"
void LimitCtrlRateInputFun(void *p)
{
    LimitCtrlRateInput *pIp = (LimitCtrlRateInput*)p;

	float32 Tr32Float_ret;
	IPCREATE(Tr32Float, ipTr32Float, .pA = 0, .ret = &(Tr32Float_ret));
	IPCALL(ipTr32Float);

	pIp -> pSCtrl[0].Ud = pIp -> pSA->rate[0] - Tr32Float_ret;

    float32 Tr32Float_ret;
    IPCREATE(Tr32Float, ipTr32Float, .pA = 0, .ret = &(Tr32Float_ret));
    IPCALL(ipTr32Float);

    pIp -> pSCtrl[1].Ud = pIp -> pSA->rate[1] - Tr32Float_ret;
    pIp -> pSCtrl[2].Ud = pIp -> pSA->rate[2] ;

    float32 LimitFloat32_ret;
    IPCREATE(LimitFloat32, ipLimitFloat32, .fin = pIp->pSCtrl[0].Ud, .fbound =  pIp->max, .ret = &(LimitFloat32_ret));
    IPCALL(ipLimitFloat32);

    pIp -> pSCtrl[0].Ud = LimitFloat32_ret;

    float32 LimitFloat32_ret;
    IPCREATE(LimitFloat32, ipLimitFloat32, .fin = pIp->pSCtrl[1].Ud, .fbound =  pIp->max, .ret = &(LimitFloat32_ret));
    IPCALL(ipLimitFloat32);

    pIp -> pSCtrl[1].Ud = LimitFloat32_ret;

    float32 LimitFloat32_ret;
    IPCREATE(LimitFloat32, ipLimitFloat32, .fin = pIp->pSCtrl[2].Ud, .fbound =  pIp->max, .ret = &(LimitFloat32_ret));
    IPCALL(ipLimitFloat32);

    pIp -> pSCtrl[2].Ud = LimitFloat32_ret;

	return;
}