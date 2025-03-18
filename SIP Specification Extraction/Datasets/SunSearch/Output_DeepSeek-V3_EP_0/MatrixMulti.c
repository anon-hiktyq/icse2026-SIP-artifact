
#include "MatrixMulti.h"

/*@ axiomatic MatrixMultiplication {
      logic real sum(real* array, integer begin, integer end) reads array[begin .. (end-1)];
      axiom empty:
        \forall real* a, integer b, e; b >= e ==> sum(a,b,e) == 0.0;
      axiom range:
        \forall real* a, integer b, e; b < e ==> sum(a,b,e) == sum(a,b,e-1) + a[e-1];
    }
*/

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->product + (0 .. pIp->nrow * pIp->ncol - 1));
  requires \valid(pIp->faciend + (0 .. pIp->nrow * pIp->nrc - 1));
  requires \valid(pIp->multiplier + (0 .. pIp->nrc * pIp->ncol - 1));
  assigns pIp->product[0 .. pIp->nrow * pIp->ncol - 1];
  ensures \forall integer i; 0 <= i < pIp->nrow * pIp->ncol ==> 
            pIp->product[i] == sum(\lambda integer k; 0 <= k < pIp->nrc; 
              pIp->faciend[(i / pIp->ncol) * pIp->nrc + k] * pIp->multiplier[k * pIp->ncol + (i % pIp->ncol)]);
*/
void MatrixMultiFun(MatrixMulti *pIp)
{
    unint08 ir;
    unint08 jc;
    unint08 nk;
    unint08 index;

    /*@ loop invariant 0 <= ir <= pIp->nrow;
        loop invariant \forall integer i; 0 <= i < ir ==> 
          \forall integer j; 0 <= j < pIp->ncol ==> 
            pIp->product[i * pIp->ncol + j] == sum(\lambda integer k; 0 <= k < pIp->nrc; 
              pIp->faciend[i * pIp->nrc + k] * pIp->multiplier[k * pIp->ncol + j]);
        loop assigns ir, jc, nk, index, pIp->product[0 .. pIp->nrow * pIp->ncol - 1];
        loop variant pIp->nrow - ir;
    */
    for (ir = 0; ir < pIp->nrow; ir++)
    {
        /*@ loop invariant 0 <= jc <= pIp->ncol;
            loop invariant \forall integer j; 0 <= j < jc ==> 
              pIp->product[ir * pIp->ncol + j] == sum(\lambda integer k; 0 <= k < pIp->nrc; 
                pIp->faciend[ir * pIp->nrc + k] * pIp->multiplier[k * pIp->ncol + j]);
            loop assigns jc, nk, index, pIp->product[ir * pIp->ncol .. (ir + 1) * pIp->ncol - 1];
            loop variant pIp->ncol - jc;
        */
        for (jc = 0; jc < pIp->ncol; jc++)
        {
            index = ir * pIp->ncol + jc;

            pIp->product[index] = 0.0f;

            /*@ loop invariant 0 <= nk <= pIp->nrc;
                loop invariant pIp->product[index] == sum(\lambda integer k; 0 <= k < nk; 
                  pIp->faciend[ir * pIp->nrc + k] * pIp->multiplier[k * pIp->ncol + jc]);
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
