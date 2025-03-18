
#include "ThrusterCtrlLogic.h"
#include "PseudoRateModulator.h"
#include "LimitFloat32.h"
#include "ThreeAxisController.h"

/*@ 
  @ requires pIp != \null;
  @ requires \forall integer i; 0 <= i < 3 ==> 
  @     (pIp->mController[i].Up >= 0 && pIp->mController[i].Ud >= 0 &&
  @      pIp->CTRL_PARAM_SAM[i].Kp >= 0 && pIp->CTRL_PARAM_SAM[i].Kd >= 0);
  @ ensures \forall integer i; 0 <= i < 3 ==> 
  @     (pIp->mController[i].fy == 
  @      pIp->mController[i].Up * pIp->CTRL_PARAM_SAM[i].Kp + 
  @      pIp->mController[i].Ud * pIp->CTRL_PARAM_SAM[i].Kd);
  @ ensures \forall integer i; 0 <= i < 3 ==> 
  @     (pIp->mModulator[i].u >= -1.3f && pIp->mModulator[i].u <= 1.3f);
  @ ensures \forall integer i; 0 <= i < 3 ==> 
  @     (pIp->mModulator[i].u == LimitFloat32(pIp->mController[i].fy, 1.3f));
  @*/
void ThreeAxisControllerFun(ThreeAxisController *pIp)
{
    pIp -> mController[0].fy = pIp -> mController[0].Up * pIp -> CTRL_PARAM_SAM[0].Kp + pIp -> mController[0].Ud * pIp -> CTRL_PARAM_SAM[0].Kd ;
    pIp -> mController[1].fy = pIp -> mController[1].Up * pIp -> CTRL_PARAM_SAM[1].Kp + pIp -> mController[1].Ud * pIp -> CTRL_PARAM_SAM[1].Kd ;
    pIp -> mController[2].fy = pIp -> mController[2].Ud * pIp -> CTRL_PARAM_SAM[2].Kd ;

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

    return ;
}
