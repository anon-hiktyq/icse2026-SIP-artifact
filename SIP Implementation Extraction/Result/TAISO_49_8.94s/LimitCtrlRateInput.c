#include "LimitCtrlRateInput.h"
void LimitCtrlRateInputFun(void *p) 
{
    LimitCtrlRateInput *pIp = (LimitCtrlRateInput*)p;

	pIp -> pSCtrl[0].Ud = pIp -> pSA->rate[0] - TR32_BIAS_WXRO() ;	/* ���ٶȼ�ƫ���� */
    {float32 Tr32Float_ret_3;IPCALL(Tr32Float,ipTr32Float_0,.ret = &Tr32Float_ret_3);pIp->pSCtrl[1].Ud = pIp->pSA->rate[1] - Tr32Float_ret_3;};	/* ���ٶȼ�ƫ���� */
    pIp -> pSCtrl[2].Ud = pIp -> pSA->rate[2] ;						/* Z����ٶ���ƫ�� */

    {float32 LimitFloat32_ret_2;IPCALL(LimitFloat32,ipLimitFloat32_2,.fin = pSCtrl[0].Ud,.fbound = max,.ret = &LimitFloat32_ret_2);pIp->pSCtrl[0].Ud = LimitFloat32_ret_2;};	/* ���ٶ��޷�1.2�� */
    {float32 LimitFloat32_ret_1;IPCALL(LimitFloat32,ipLimitFloat32_1,.fin = pSCtrl[1].Ud,.fbound = max,.ret = &LimitFloat32_ret_1);pIp->pSCtrl[1].Ud = LimitFloat32_ret_1;};
    {float32 LimitFloat32_ret_0;IPCALL(LimitFloat32,ipLimitFloat32_0,.fin = pSCtrl[2].Ud,.fbound = max,.ret = &LimitFloat32_ret_0);pIp->pSCtrl[2].Ud = LimitFloat32_ret_0;};

	return;
}