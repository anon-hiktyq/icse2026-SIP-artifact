
#include "ThrusterCtrlLogic.h"
#include "PseudoRateModulator.h"
#include "LimitFloat32.h"
#include "ThreeAxisController.h"

/*@ 
requires \valid(pIp);
requires \valid(pIp->mController + (0..2));
requires \valid(pIp->CTRL_PARAM_SAM + (0..2));
requires \valid(pIp->mModulator + (0..2));
assigns pIp->mController[0].fy;
assigns pIp->mController[1].fy;
assigns pIp->mController[2].fy;
assigns pIp->mModulator[0].u;
assigns pIp->mModulator[1].u;
assigns pIp->mModulator[2].u;
ensures pIp->mModulator[0].u == \old(pIp->mModulator[0].u) || pIp->mModulator[0].u == 1.3f || pIp->mModulator[0].u == -1.3f;
ensures pIp->mModulator[1].u == \old(pIp->mModulator[1].u) || pIp->mModulator[1].u == 1.3f || pIp->mModulator[1].u == -1.3f;
ensures pIp->mModulator[2].u == \old(pIp->mModulator[2].u) || pIp->mModulator[2].u == 1.3f || pIp->mModulator[2].u == -1.3f;
*/
void ThreeAxisControllerFun(ThreeAxisController *pIp)
{
    pIp -> mController[0].fy = pIp -> mController[0].Up * pIp -> CTRL_PARAM_SAM[0].Kp + pIp -> mController[0].Ud * pIp -> CTRL_PARAM_SAM[0].Kd;
    pIp -> mController[1].fy = pIp -> mController[1].Up * pIp -> CTRL_PARAM_SAM[1].Kp + pIp -> mController[1].Ud * pIp -> CTRL_PARAM_SAM[1].Kd;
    pIp -> mController[2].fy = pIp -> mController[2].Ud * pIp -> CTRL_PARAM_SAM[2].Kd;

    float32 LimitFloat32_ret_0;
    IPCREATE(LimitFloat32, ipLimitFloat32_0, .fin = pIp->mController[0].fy, .fbound =  1.3f, .ret = &(LimitFloat32_ret_0));
    IPCALL(ipLimitFloat32_0);

    pIp -> mModulator[0].u = LimitFloat32_ret_0;

    float32 LimitFloat32_ret_1;
    IPCREATE(LimitFloat32, ipLimitFloat32_1, .fin = pIp->mController[1].fy, .fbound =  1.3f, .ret = &(LimitFloat32_ret_1));
    IPCALL(ipLimitFloat32_1);

    pIp -> mModulator[1].u = LimitFloat32_ret_1;

    float32 LimitFloat32_ret_2;
    IPCREATE(LimitFloat32, ipLimitFloat32_2, .fin = pIp->mController[2].fy, .fbound =  1.3f, .ret = &(LimitFloat32_ret_2));
    IPCALL(ipLimitFloat32_2);

    pIp -> mModulator[2].u = LimitFloat32_ret_2;

    IPCREATE(PseudoRateModulator, ipPseudoRateModulator_0, .pModulator = &(pIp->mModulator[0]), .h1 =  pIp->CTRL_PARAM_SAM[0].h1);
    IPCALL(ipPseudoRateModulator_0);

    IPCREATE(PseudoRateModulator, ipPseudoRateModulator_1, .pModulator = &(pIp->mModulator[1]), .h1 =  pIp->CTRL_PARAM_SAM[1].h1);
    IPCALL(ipPseudoRateModulator_1);

    IPCREATE(PseudoRateModulator, ipPseudoRateModulator_2, .pModulator = &(pIp->mModulator[2]), .h1 =  pIp->CTRL_PARAM_SAM[2].h1);
    IPCALL(ipPseudoRateModulator_2);

    IPCREATE(ThrusterCtrlLogic, ipThrusterCtrlLogic);
    IPCALL(ipThrusterCtrlLogic);

    return;
}
