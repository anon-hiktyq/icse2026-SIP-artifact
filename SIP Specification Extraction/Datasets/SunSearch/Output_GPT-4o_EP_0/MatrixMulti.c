
#include "MatrixMulti.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->faciend + (0 .. pIp->nrow * pIp->nrc - 1));
  requires \valid(pIp->multiplier + (0 .. pIp->nrc * pIp->ncol - 1));
  requires \valid(pIp->product + (0 .. pIp->nrow * pIp->ncol - 1));
  requires pIp->nrow > 0 && pIp->ncol > 0 && pIp->nrc > 0;
  assigns pIp->product[0 .. pIp->nrow * pIp->ncol - 1];
  ensures \forall integer i; 0 <= i < pIp->nrow * pIp->ncol ==> pIp->product[i] == 
          \sum(0, pIp->nrc, \lambda integer k; pIp->faciend[(i / pIp->ncol) * pIp->nrc + k] * pIp->multiplier[k * pIp->ncol + (i % pIp->ncol)]);
*/
void MatrixMultiFun(MatrixMulti *pIp)
{
    unint08 ir;
    unint08 jc;
    unint08 nk;
    unint08 index;

    /*@ loop invariant 0 <= ir <= pIp->nrow;
        loop assigns ir, jc, nk, index, pIp->product[0 .. pIp->nrow * pIp->ncol - 1];
        loop variant pIp->nrow - ir;
    */
    for (ir = 0; ir < pIp->nrow; ir++)
    {
        /*@ loop invariant 0 <= jc <= pIp->ncol;
            loop assigns jc, nk, index, pIp->product[ir * pIp->ncol .. (ir + 1) * pIp->ncol - 1];
            loop variant pIp->ncol - jc;
        */
        for (jc = 0; jc < pIp->ncol; jc++)
        {
            index = ir * pIp->ncol + jc;
            pIp->product[index] = 0.0f;

            /*@ loop invariant 0 <= nk <= pIp->nrc;
                loop assigns nk, pIp->product[index];
                loop variant pIp->nrc - nk;
            */
            for (nk = 0; nk < pIp->nrc; nk++)
            {
                pIp->product[index] = pIp->product[index] + pIp->faciend[ir * pIp->nrc + nk] * pIp->multiplier[nk * pIp->ncol + jc];
            }
        }
    }

    return;
}
