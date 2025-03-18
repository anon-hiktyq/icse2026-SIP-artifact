
#include "MatrixMulti.h"

/*@ 
  requires pIp != \null;
  requires \valid(pIp->faciend + (0..pIp->nrow * pIp->nrc - 1));
  requires \valid(pIp->multiplier + (0..pIp->nrc * pIp->ncol - 1));
  requires \valid(pIp->product + (0..pIp->nrow * pIp->ncol - 1));
  requires pIp->nrow >= 0;
  requires pIp->ncol >= 0;
  requires pIp->nrc >= 0;
  assigns pIp->product[0..pIp->nrow * pIp->ncol - 1];
  ensures \forall integer ir, jc; 
          0 <= ir < pIp->nrow && 0 <= jc < pIp->ncol ==> 
          pIp->product[ir * pIp->ncol + jc] == 
          \sum(0 <= nk < pIp->nrc, 
               pIp->faciend[ir * pIp->nrc + nk] * pIp->multiplier[nk * pIp->ncol + jc]);
*/
void MatrixMultiFun(MatrixMulti *pIp)
{
    unsigned char ir; 
    unsigned char jc; 
    unsigned char nk; 
    unsigned int index; 

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
