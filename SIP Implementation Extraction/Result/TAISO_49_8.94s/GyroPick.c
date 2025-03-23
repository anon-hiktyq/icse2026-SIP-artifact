#include "GyroPick.h"
void GyroPickFun(void *p) 
{
    GyroPick *pIp = (GyroPick*)p;

    unint08 iy ;
    float32 tmpgi ;

    for ( iy = 0 ; iy < 9 ; iy++ )
    {

        tmpgi = ABS(pIp -> pGyroData->wa[iy] - pIp -> pGyroData->wal[iy]) ;	/* �Ƕ�������Ұ���� */

        if (tmpgi > 0.048f)    								/* ��Ұ��0.048��/s */
        {
            pIp -> pGyroData->countPick[iy]++ ;						/* Ұֵ������ */

            if (pIp -> pGyroData->countPick[iy] < 6)   				/* û��6������Ұֵ */
            {
                pIp -> pGyroData->wa[iy] = pIp -> pGyroData->wal[iy] ;		/* �������ڵ�ֵ���汾���ڵ�ֵ */

            }
            else                                			/* ����6����Ұֵ */
            {
                pIp -> pGyroData->wal[iy] = pIp -> pGyroData->wa[iy] ;		/* �ñ����ڵ�ֵ���������ڵ�ֵ */

                pIp -> pGyroData->countPick[iy] = 0 ;				/* �����Ұֵ���������� */

            }
        }
        else                     							/* û�г�����Ұ�� */
        {
            pIp -> pGyroData->wal[iy] = pIp -> pGyroData->wa[iy] ;			/* ����ֵ */

            pIp -> pGyroData->countPick[iy] = 0 ;					/* Ұֵ���������� */

        }
    }

    return ;

}