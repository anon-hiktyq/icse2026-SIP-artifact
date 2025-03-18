
#include "MatrixTran.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->mat + (0..(pIp->nrow * pIp->ncol - 1)));
  requires \valid(pIp->tran + (0..(pIp->ncol * pIp->nrow - 1)));
  requires pIp->nrow > 0 && pIp->ncol > 0;
  assigns pIp->tran[0..(pIp->ncol * pIp->nrow - 1)];
*/
void MatrixTranFun(MatrixTran *pIp)
{
    unint08 i;
    unint08 j;

    /*@ loop invariant 0 <= i <= pIp->nrow;
        loop variant pIp->nrow - i;
    */
    for (i = 0; i < pIp->nrow; i++)
    {
        /*@ loop invariant 0 <= j <= pIp->ncol;
            loop variant pIp->ncol - j;
        */
        for (j = 0; j < pIp->ncol; j++)
        {
            *(pIp->tran + j * pIp->nrow + i) = *(pIp->mat + i * pIp->ncol + j);
        }
    }

    return;
}
