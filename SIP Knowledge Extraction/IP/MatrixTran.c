#include "MatrixTran.h"
void MatrixTranFun(void *p)
{
    MatrixTran *pIp = (MatrixTran*)p;

    unint08 i ;
    unint08 j ;

    for ( i=0 ; i<pIp -> nrow ; i++ )
    {
        for ( j=0 ; j<pIp -> ncol ; j++ )
        {
            *(pIp -> tran + j * pIp -> nrow + i) = *(pIp -> mat + i * pIp -> ncol + j) ;
        }
    }

    return ;
}