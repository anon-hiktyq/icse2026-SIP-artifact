
#include "MatrixTran.h"

/*@ axiomatic MatrixProperties {
      predicate valid_matrix(float32* mat, integer rows, integer cols) = 
         \valid(mat + (0..rows*cols-1));
      predicate valid_transpose(float32* tran, integer rows, integer cols) = 
         \valid(tran + (0..rows*cols-1));
    }
*/

/*@ requires \valid(pIp);
    requires valid_matrix(pIp->mat, pIp->nrow, pIp->ncol);
    requires valid_transpose(pIp->tran, pIp->ncol, pIp->nrow);
    ensures \forall integer i, j; 0 <= i < pIp->nrow && 0 <= j < pIp->ncol ==>
            *(pIp->tran + j * pIp->nrow + i) == \old(*(pIp->mat + i * pIp->ncol + j));
    assigns pIp->tran[0..(pIp->nrow * pIp->ncol - 1)];
*/
void MatrixTranFun(MatrixTran *pIp)
{
    unint08 i;
    unint08 j;

    /*@ ghost float32 mat_initial[pIp->nrow * pIp->ncol];
        // Initialize mat_initial using a logical assertion
        //@ assert \forall integer k; 0 <= k < pIp->nrow * pIp->ncol ==> mat_initial[k] == \old(*(pIp->mat + k));
    */

    /*@ loop invariant 0 <= i <= pIp->nrow;
        loop invariant \forall integer k, l; 0 <= k < i && 0 <= l < pIp->ncol ==>
                       *(pIp->tran + l * pIp->nrow + k) == mat_initial[k * pIp->ncol + l];
        loop assigns i, j, pIp->tran[0..(pIp->nrow * pIp->ncol - 1)];
        loop variant pIp->nrow - i;
    */
    for (i = 0; i < pIp->nrow; i++)
    {
        /*@ loop invariant 0 <= j <= pIp->ncol;
            loop invariant \forall integer l; 0 <= l < j ==>
                           *(pIp->tran + l * pIp->nrow + i) == mat_initial[i * pIp->ncol + l];
            loop assigns j, pIp->tran[0..(pIp->nrow * pIp->ncol - 1)];
            loop variant pIp->ncol - j;
        */
        for (j = 0; j < pIp->ncol; j++)
        {
            *(pIp->tran + j * pIp->nrow + i) = *(pIp->mat + i * pIp->ncol + j);
        }
    }

    return;
}
