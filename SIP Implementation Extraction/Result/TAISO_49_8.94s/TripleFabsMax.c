#include "TripleFabsMax.h"
void TripleFabsMaxFun(void *p) 
{
    TripleFabsMax *pIp = (TripleFabsMax*)p;

    float32 fabsfx1 ;			                            /* ����1�ľ���ֵ */
    float32 fabsfy2 ;			                            /* ����2�ľ���ֵ */
    float32 fabsfz3 ;			                            /* ����3�ľ���ֵ */
    float32 pIp -> tmax ;				                            /* ���ֵ */

    /* Ĭ��Ϊ�� */
    fabsfx1 = pIp -> fx1;                                          /* ����ֵ1 */
    fabsfy2 = pIp -> fy2;                                          /* ����ֵ2 */
    fabsfz3 = pIp -> fz3;                                          /* ����ֵ3 */

    /* ȡ����ֵ1 */
    if (pIp -> fx1 < 0.0f)
    {
        fabsfx1 = -pIp -> fx1;                                     /* ����1Ϊ�� */
    }

    /* ȡ����ֵ2 */
    if (pIp -> fy2 < 0.0f)
    {
        fabsfy2 = -pIp -> fy2;                                     /* ����2Ϊ�� */
    }

    /* ȡ����ֵ3 */
    if (pIp -> fz3 < 0.0f)
    {
        fabsfz3 = -pIp -> fz3;                                     /* ����3Ϊ�� */
    }

    /* ����1����2����ֵ�����ֵ */
    if (fabsfx1 > fabsfy2)
    {
        pIp -> tmax = fabsfx1 ;	                                /* 1����ֵ�� */
    }
    else
    {
        pIp -> tmax = fabsfy2 ;	                                /* 2����ֵ�� */
    }

     /* ����1��2���ֵ����3����ֵ�����ֵ */
    if (fabsfz3 > pIp -> tmax)
    {
        pIp -> tmax = fabsfz3 ;	                                /* 3����ֵ�� */
    }

    *(pIp -> ret) = tmax ;
}