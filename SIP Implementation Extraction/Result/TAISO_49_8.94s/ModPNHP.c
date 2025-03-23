#include "ModPNHP.h"
void ModPNHPFun(void *p) 
{
    ModPNHP *pIp = (ModPNHP*)p;

    float32 period;                                         /* ���� */
    float32 pIp -> npp2;                                           /* �޷���ķ���ֵ */

    /* ��������ֵ */
    period = 2.0f * pIp -> halfperiod;

    pIp -> npp2 = pIp -> x - (pIp -> x + pIp -> halfperiod) / period * period;   /* �޷������� */

    *(pIp -> ret) = npp2;
    }