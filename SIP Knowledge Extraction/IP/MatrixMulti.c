#include "MatrixMulti.h"
void MatrixMultiFun(void *p)
{
    MatrixMulti *pIp = (MatrixMulti*)p;

    unint08 ir ;
    unint08 jc ;
    unint08 nk ;
    unint08 index ;

    for (ir=0 ; ir<pIp -> nrow ; ir++)
    {
        for (jc=0 ; jc<pIp -> ncol ; jc++)
        {
            index = ir * pIp -> ncol + jc ;

            pIp -> product[index] = 0.0f ;

            for (nk=0 ; nk<pIp -> nrc ; nk++)
            {
                pIp -> product[index] = pIp -> product[index] + pIp -> faciend[ir * pIp -> nrc + nk] * pIp -> multiplier[nk * pIp -> ncol + jc] ;
            }
        }
    }

    return ;
}