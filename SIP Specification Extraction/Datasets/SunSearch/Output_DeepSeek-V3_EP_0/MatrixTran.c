
#include "MatrixTran.h"

/*@ axiomatic MatrixProperties {
      predicate valid_matrix(int* mat, integer nrow, integer ncol) = 
         \valid(mat + (0..nrow*ncol-1));
      predicate valid_transpose(int* tran, integer nrow, integer ncol) = 
         \valid(tran + (0..nrow*ncol-1));
    }
*/

/*@ requires \valid(pIp);
    requires valid_matrix(pIp->mat, pIp->nrow, pIp->ncol);
    requires valid_transpose(pIp->tran, pIp->nrow, pIp->ncol);
    requires pIp->nrow > 0 && pIp->ncol > 0;
    assigns pIp->tran[0..pIp->nrow*pIp->ncol-1];
    ensures \forall unint08 i, j; 0 <= i < pIp->nrow && 0 <= j < pIp->ncol ==>
            *(pIp->tran + j * pIp->nrow + i) == \old(*(pIp->mat + i * pIp->ncol + j));
*/
void MatrixTranFun(MatrixTran *pIp)
{
    unint08 i;
    unint08 j;

    /*@ loop invariant 0 <= i <= pIp->nrow;
        loop invariant \forall unint08 k, l; 0 <= k < i && 0 <= l < pIp->ncol ==>
                       *(pIp->tran + l * pIp->nrow + k) == \old(*(pIp->mat + k * pIp->ncol + l));
        loop assigns i, j, pIp->tran[0..pIp->nrow*pIp->ncol-1];
        loop variant pIp->nrow - i;
    */
    for (i = 0; i < pIp->nrow; i++)
    {
        /*@ loop invariant 0 <= j <= pIp->ncol;
            loop invariant \forall unint08 l; 0 <= l < j ==>
                           *(pIp->tran + l * pIp->nrow + i) == \old(*(pIp->mat + i * pIp->ncol + l));
            loop assigns j, pIp->tran[0..pIp->nrow*pIp->ncol-1];
            loop variant pIp->ncol - j;
        */
        for (j = 0; j < pIp->ncol; j++)
        {
            *(pIp->tran + j * pIp->nrow + i) = *(pIp->mat + i * pIp->ncol + j);
        }
    }

    return;
}
