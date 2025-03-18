
#include "MatrixTran.h"

/*@ 
  requires pIp != \null;
  requires \valid(pIp);
  requires \valid(pIp->mat + (0..(pIp->nrow * pIp->ncol - 1)));
  requires \valid(pIp->tran + (0..(pIp->ncol * pIp->nrow - 1)));
  requires pIp->nrow >= 0;
  requires pIp->ncol >= 0;
  assigns pIp->tran[0..(pIp->ncol * pIp->nrow - 1)];

  ensures \forall unint08 i; 0 <= i < pIp->nrow ==>
          \forall unint08 j; 0 <= j < pIp->ncol ==>
          pIp->tran[j * pIp->nrow + i] == pIp->mat[i * pIp->ncol + j];
*/
void MatrixTranFun(MatrixTran *pIp)
{
    unint08 i;
    unint08 j;

    /*@
      loop invariant 0 <= i <= pIp->nrow;
      loop assigns j;
      loop variant pIp->nrow - i;
    */
    for (i = 0; i < pIp->nrow; i++)
    {
        /*@
          loop invariant 0 <= j <= pIp->ncol;
          loop assigns j;
          loop variant pIp->ncol - j;
        */
        for (j = 0; j < pIp->ncol; j++)
        {
            *(pIp->tran + j * pIp->nrow + i) = *(pIp->mat + i * pIp->ncol + j);
        }
    }

    return;
}
