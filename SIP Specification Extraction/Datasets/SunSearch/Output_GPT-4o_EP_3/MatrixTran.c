
#include "MatrixTran.h"

/*@ 
requires \valid(pIp);
requires \valid(pIp->mat + (0 .. pIp->nrow * pIp->ncol - 1));
requires \valid(pIp->tran + (0 .. pIp->nrow * pIp->ncol - 1));
requires pIp->nrow > 0;
requires pIp->ncol > 0;
assigns pIp->tran[0 .. pIp->nrow * pIp->ncol - 1];
*/
void MatrixTranFun(MatrixTran *pIp)
{
    unint08 i;
    unint08 j;

    /*@ loop invariant 0 <= i <= pIp->nrow;
        loop invariant \forall unint08 k; 0 <= k < i ==> 
            \forall unint08 l; 0 <= l < pIp->ncol ==> 
                pIp->tran[l * pIp->nrow + k] == pIp->mat[k * pIp->ncol + l];
        loop assigns i, j, pIp->tran[0 .. pIp->nrow * pIp->ncol - 1];
        loop variant pIp->nrow - i;
    */
    for (i = 0; i < pIp->nrow; i++)
    {
        /*@ loop invariant 0 <= j <= pIp->ncol;
            loop invariant \forall unint08 k; 0 <= k <= i ==> 
                \forall unint08 l; 0 <= l < (k < i ? pIp->ncol : j) ==> 
                    pIp->tran[l * pIp->nrow + k] == pIp->mat[k * pIp->ncol + l];
            loop assigns j, pIp->tran[0 .. pIp->nrow * pIp->ncol - 1];
            loop variant pIp->ncol - j;
        */
        for (j = 0; j < pIp->ncol; j++)
        {
            *(pIp->tran + j * pIp->nrow + i) = *(pIp->mat + i * pIp->ncol + j);
        }
    }

    return;
}
