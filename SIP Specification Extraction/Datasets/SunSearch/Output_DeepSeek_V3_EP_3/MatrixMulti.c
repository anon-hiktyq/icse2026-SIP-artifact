
#include "MatrixMulti.h"

/*@ axiomatic Sum_array {
      logic float sum(float* array, integer begin, integer end) reads array[begin .. (end-1)];
      axiom empty:
        \forall float* a, integer b, e; b >= e ==> sum(a,b,e) == 0.0;
      axiom range:
        \forall float* a, integer b, e; b < e ==> sum(a,b,e) == sum(a,b,e-1) + a[e-1];
    }
*/

/*@
  requires \valid(pIp);
  requires \valid(pIp->product + (0 .. pIp->nrow * pIp->ncol - 1));
  requires \valid(pIp->faciend + (0 .. pIp->nrow * pIp->nrc - 1));
  requires \valid(pIp->multiplier + (0 .. pIp->nrc * pIp->ncol - 1));
  assigns pIp->product[0 .. pIp->nrow * pIp->ncol - 1];
  ensures \forall integer i, j; 0 <= i < pIp->nrow && 0 <= j < pIp->ncol ==>
            pIp->product[i * pIp->ncol + j] == 
              sum(pIp->faciend, i * pIp->nrc, (i+1) * pIp->nrc) * 
              sum(pIp->multiplier, j * pIp->ncol, (j+1) * pIp->ncol);
*/
void MatrixMultiFun(MatrixMulti *pIp) {
    unint08 ir;
    unint08 jc;
    unint08 nk;
    unint08 index;

    /*@
      loop invariant 0 <= ir <= pIp->nrow;
      loop invariant \forall integer i, j; 0 <= i < ir && 0 <= j < pIp->ncol ==>
                       pIp->product[i * pIp->ncol + j] == 
                         sum(pIp->faciend, i * pIp->nrc, (i+1) * pIp->nrc) * 
                         sum(pIp->multiplier, j * pIp->ncol, (j+1) * pIp->ncol);
      loop assigns pIp->product[0 .. pIp->nrow * pIp->ncol - 1];
      loop variant pIp->nrow - ir;
    */
    for (ir = 0; ir < pIp->nrow; ir++) {
        /*@
          loop invariant 0 <= jc <= pIp->ncol;
          loop invariant \forall integer j; 0 <= j < jc ==>
                           pIp->product[ir * pIp->ncol + j] == 
                             sum(pIp->faciend, ir * pIp->nrc, (ir+1) * pIp->nrc) * 
                             sum(pIp->multiplier, j * pIp->ncol, (j+1) * pIp->ncol);
          loop assigns pIp->product[ir * pIp->ncol .. (ir+1) * pIp->ncol - 1];
          loop variant pIp->ncol - jc;
        */
        for (jc = 0; jc < pIp->ncol; jc++) {
            index = ir * pIp->ncol + jc;
            pIp->product[index] = 0.0f;

            /*@
              loop invariant 0 <= nk <= pIp->nrc;
              loop invariant pIp->product[index] == 
                               sum(pIp->faciend, ir * pIp->nrc, ir * pIp->nrc + nk) * 
                               sum(pIp->multiplier, jc * pIp->ncol, (jc+1) * pIp->ncol);
              loop assigns pIp->product[index];
              loop variant pIp->nrc - nk;
            */
            for (nk = 0; nk < pIp->nrc; nk++) {
                pIp->product[index] = pIp->product[index] + 
                                      pIp->faciend[ir * pIp->nrc + nk] * 
                                      pIp->multiplier[nk * pIp->ncol + jc];
            }
        }
    }

    return;
}
