#include "ThrusterCtrlLogic.h"
#include "PseudoRateModulator.h"
#include "LimitFloat32.h"
#include "ThreeAxisController.h"
void ThreeAxisControllerFun(void *p)
{
    ThreeAxisController *pIp = (ThreeAxisController*)p;

    pIp -> mController[0].fy = pIp -> mController[0].Up * pIp -> CTRL_PARAM_SAM[0].Kp + pIp -> mController[0].Ud * pIp -> CTRL_PARAM_SAM[0].Kd ;
    pIp -> mController[1].fy = pIp -> mController[1].Up * pIp -> CTRL_PARAM_SAM[1].Kp + pIp -> mController[1].Ud * pIp -> CTRL_PARAM_SAM[1].Kd ;
    pIp -> mController[2].fy = pIp -> mController[2].Ud * pIp -> CTRL_PARAM_SAM[2].Kd ;

    float32 LimitFloat32_ret;
    IPCREATE(LimitFloat32, ipLimitFloat32, .fin = pIp->mController[0].fy, .fbound =  1.3f, .ret = &(LimitFloat32_ret));
    IPCALL(ipLimitFloat32);

    pIp -> mModulator[0].u = LimitFloat32_ret;

    float32 LimitFloat32_ret;
    IPCREATE(LimitFloat32, ipLimitFloat32, .fin = pIp->mController[1].fy, .fbound =  1.3f, .ret = &(LimitFloat32_ret));
    IPCALL(ipLimitFloat32);

    pIp -> mModulator[1].u = LimitFloat32_ret;

    float32 LimitFloat32_ret;
    IPCREATE(LimitFloat32, ipLimitFloat32, .fin = pIp->mController[2].fy, .fbound =  1.3f, .ret = &(LimitFloat32_ret));
    IPCALL(ipLimitFloat32);

    pIp -> mModulator[2].u = LimitFloat32_ret;

    IPCREATE(PseudoRateModulator, ipPseudoRateModulator, .pModulator = &(pIp->mModulator[0]), .h1 =  pIp->CTRL_PARAM_SAM[0].h1);
    IPCALL(ipPseudoRateModulator);

    IPCREATE(PseudoRateModulator, ipPseudoRateModulator, .pModulator = &(pIp->mModulator[1]), .h1 =  pIp->CTRL_PARAM_SAM[1].h1);
    IPCALL(ipPseudoRateModulator);

    IPCREATE(PseudoRateModulator, ipPseudoRateModulator, .pModulator = &(pIp->mModulator[2]), .h1 =  pIp->CTRL_PARAM_SAM[2].h1);
    IPCALL(ipPseudoRateModulator);

    IPCREATE(ThrusterCtrlLogic, ipThrusterCtrlLogic);
    IPCALL(ipThrusterCtrlLogic);

	return ;
}