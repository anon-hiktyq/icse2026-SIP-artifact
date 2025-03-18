
#include "MatrixTran.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->mat + (0..(pIp->nrow * pIp->ncol - 1)));
  requires \valid(pIp->tran + (0..(pIp->nrow * pIp->ncol - 1)));
  requires pIp->nrow > 0 && pIp->ncol > 0;
  assigns pIp->tran[0..(pIp->nrow * pIp->ncol - 1)];
  ensures \forall unint08 i, j; 0 <= i < pIp->nrow && 0 <= j < pIp->ncol ==> 
          pIp->tran[j * pIp->nrow + i] == pIp->mat[i * pIp->ncol + j];
*/
void MatrixTranFun(MatrixTran *pIp)
{
    unint08 i;
    unint08 j;

    /*@ loop invariant 0 <= i <= pIp->nrow;
        loop invariant \forall unint08 ii, jj; 0 <= ii < i && 0 <= jj < pIp->ncol ==> 
                       pIp->tran[jj * pIp->nrow + ii] == pIp->mat[ii * pIp->ncol + jj];
        loop assigns i, j, pIp->tran[0..(pIp->nrow * pIp->ncol - 1)];
        loop variant pIp->nrow - i;
    */
    for (i = 0; i < pIp->nrow; i++)
    {
        /*@ loop invariant 0 <= j <= pIp->ncol;
            loop invariant \forall unint08 jj; 0 <= jj < j ==> 
                           pIp->tran[jj * pIp->nrow + i] == pIp->mat[i * pIp->ncol + jj];
            loop assigns j, pIp->tran[i + j * pIp->nrow];
            loop variant pIp->ncol - j;
        */
        for (j = 0; j < pIp->ncol; j++)
        {
            *(pIp->tran + j * pIp->nrow + i) = *(pIp->mat + i * pIp->ncol + j);
        }
    }

    return;
}
