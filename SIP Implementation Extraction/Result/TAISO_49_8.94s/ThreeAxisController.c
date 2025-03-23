#include "ThreeAxisController.h"
void ThreeAxisControllerFun(void *p) 
{
    ThreeAxisController *pIp = (ThreeAxisController*)p;

	/* ������������� */
    pIp -> mController[0].fy = pIp -> mController[0].Up * pIp -> CTRL_PARAM_SAM[0].Kp + pIp -> mController[0].Ud * pIp -> CTRL_PARAM_SAM[0].Kd ;
    pIp -> mController[1].fy = pIp -> mController[1].Up * pIp -> CTRL_PARAM_SAM[1].Kp + pIp -> mController[1].Ud * pIp -> CTRL_PARAM_SAM[1].Kd ;
    pIp -> mController[2].fy = pIp -> mController[2].Ud * pIp -> CTRL_PARAM_SAM[2].Kd ;

	/* ����������޷�,α���ʵ���������,����������� */
    {float32 LimitFloat32_ret_2;IPCALL(LimitFloat32,ipLimitFloat32_2,.fin = mController[0].fy,.fbound = 1.3f,.ret = &LimitFloat32_ret_2);pIp->mModulator[0].u = LimitFloat32_ret_2;};	/* α����״̬�� */
    {float32 LimitFloat32_ret_1;IPCALL(LimitFloat32,ipLimitFloat32_1,.fin = mController[1].fy,.fbound = 1.3f,.ret = &LimitFloat32_ret_1);pIp->mModulator[1].u = LimitFloat32_ret_1;};	/* α����״̬�� */
    {float32 LimitFloat32_ret_0;IPCALL(LimitFloat32,ipLimitFloat32_0,.fin = mController[2].fy,.fbound = 1.3f,.ret = &LimitFloat32_ret_0);pIp->mModulator[2].u = LimitFloat32_ret_0;};	/* α����״̬�� */

    /* ����α���ʵ��������� */
    {IPCALL(PseudoRateModulator,ipPseudoRateModulator_2,.pModulator = &mModulator[0],.h1 = CTRL_PARAM_SAM[0].h1);};
    {IPCALL(PseudoRateModulator,ipPseudoRateModulator_1,.pModulator = &mModulator[1],.h1 = CTRL_PARAM_SAM[1].h1);};
    {IPCALL(PseudoRateModulator,ipPseudoRateModulator_0,.pModulator = &mModulator[2],.h1 = CTRL_PARAM_SAM[2].h1);};

	/* ��������Ͽ����߼� */
    {IPCALL(ThrusterCtrlLogic,ipThrusterCtrlLogic_0);};

	return ;
}