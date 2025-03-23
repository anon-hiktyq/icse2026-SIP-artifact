#include "MatrixMulti.h"
void MatrixMultiFun(void *p) 
{
    MatrixMulti *pIp = (MatrixMulti*)p;






    unint08 ir ;			                                /* ��ѭ������ */
    unint08 jc ;			                                /* ��ѭ������ */
    unint08 nk ;			                                /* ��������Ӹ��� */
    unint08 index ;			                                /* ���������λ�� */

    /* product:��ͽ������ָ�� */
    /* faciend:��;��� */
    /* multiplier:����;��� */
    /* nrow:�������� */
    /* nrc:��������Ӹ��� */
    /* ncol:�������� */

    for (ir=0 ; ir<pIp -> nrow ; ir++)                             /* ��ѭ�� */
    {
        for (jc=0 ; jc<pIp -> ncol ; jc++)                         /* ��ѭ�� */
        {
            index = ir * pIp -> ncol + jc ;		                /* ���������λ�� */

            pIp -> product[index] = 0.0f ;			                /* �˻����Ĭ��ȡ0 */

            for (nk=0 ; nk<pIp -> nrc ; nk++)                      /* ��������Ӹ���ѭ�� */
            {
                pIp -> product[index] = pIp -> product[index] + pIp -> faciend[ir * pIp -> nrc + nk] * pIp -> multiplier[nk * pIp -> ncol + jc] ;
            }
        }
    }

    return ;
}