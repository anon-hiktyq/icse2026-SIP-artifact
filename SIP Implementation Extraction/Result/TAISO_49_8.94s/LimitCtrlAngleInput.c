#include "LimitCtrlAngleInput.h"
void LimitCtrlAngleInputFun(void *p) 
{
    LimitCtrlAngleInput *pIp = (LimitCtrlAngleInput*)p;

	/* �ڽ��п���������ǰ,�������źŽ����޷� */
    pIp -> pSCtrl[0].Up = pIp -> pSA->angle[0] ;				/* �Ƕȼ�ƫ������ƫ����Ϊ0  */
    pIp -> pSCtrl[1].Up = pIp -> pSA->angle[1] ;				/* �Ƕȼ�ƫ������ƫ����Ϊ0  */
    pIp -> pSCtrl[2].Up = 0.0f ;						/* Z��Ƕ����� */

	{float32 LimitFloat32_ret_1;IPCALL(LimitFloat32,ipLimitFloat32_1,.fin = pSCtrl[0].Up,.fbound = max,.ret = &LimitFloat32_ret_1);pIp->pSCtrl[0].Up = LimitFloat32_ret_1;};	/* �Ƕ��޷�8�� */
    {float32 LimitFloat32_ret_0;IPCALL(LimitFloat32,ipLimitFloat32_0,.fin = pSCtrl[1].Up,.fbound = max,.ret = &LimitFloat32_ret_0);pIp->pSCtrl[1].Up = LimitFloat32_ret_0;};

	return;
}