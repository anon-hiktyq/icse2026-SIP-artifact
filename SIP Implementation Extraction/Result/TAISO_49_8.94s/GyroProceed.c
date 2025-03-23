#include "GyroProceed.h"
void GyroProceedFun(void *p) 
{
    GyroProceed *pIp = (GyroProceed*)p;

    float32 dgi[2] ;

    {IPCALL(GyroPick,ipGyroPick_0,.pGyroData = &mGyroData);};										    /*  B1����Ұ */

    /* B2������������ٶ� */
    {IPCALL(GyroChoose,ipGyroChoose_0,.pGyroData = &mGyroData);};											/* ����ѡ�� */
	{IPCALL(CalculateGyroRs,ipCalculateGyroRs_0,.pGyroData = &mGyroData);};
    {IPCALL(CalculateGyroDg,ipCalculateGyroDg_0,.pGyroData = &mGyroData);};										/* ����������ٶȼ��� */

    /* SAM����������Ư�Ʋ��� */
    dgi[0] = pIp -> mGyroData.Gi[0] + pIp -> mGyroData.W[0] * 0.160f ;	/* ��������0.16 */
    dgi[1] = pIp -> mGyroData.Gi[1] + pIp -> mGyroData.W[1] * 0.160f ;	/* ��������0.16 */

    /* ���ݽǶȻ���,����(-180, 180)֮�� */
    {float32 ModPNHP_ret_1;IPCALL(ModPNHP,ipModPNHP_1,.x = dgi[0],.halfperiod = 180.0f,.ret = &ModPNHP_ret_1);pIp->mGyroData.Gi[0] = ModPNHP_ret_1;};				/* �����ǻ��� = �����ڻ�����ֵ + �����ڻ��ָı�ֵ */
    {float32 ModPNHP_ret_0;IPCALL(ModPNHP,ipModPNHP_0,.x = dgi[1],.halfperiod = 180.0f,.ret = &ModPNHP_ret_0);pIp->mGyroData.Gi[1] = ModPNHP_ret_0;};			    /* �����ǻ��� = �����ڻ�����ֵ + �����ڻ��ָı�ֵ */

    return ;
}