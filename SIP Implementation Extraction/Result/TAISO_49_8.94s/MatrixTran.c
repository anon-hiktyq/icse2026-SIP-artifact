#include "MatrixTran.h"
void MatrixTranFun(void *p) 
{
    MatrixTran *pIp = (MatrixTran*)p;




	/* ע��Դ��Ŀ�����/����������ͬһ�� */
    unint08 i ;		/* ������ѭ������ */
    unint08 j ;		/* ������ѭ������ */

   /* tran:Ŀ����� */
   /* mat: Դ���� */
   /* nrow:�������� */
   /* ncol:�������� */

    for ( i=0 ; i<pIp -> nrow ; i++ )                              /* ��ѭ�� */
    {
        for ( j=0 ; j<pIp -> ncol ; j++ )                          /* ��ѭ�� */
        {
            *(pIp -> tran + j * pIp -> nrow + i) = *(pIp -> mat + i * pIp -> ncol + j) ;
        }
    }

    return ;
}