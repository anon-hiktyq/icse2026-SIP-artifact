
#include "numusearray.h"

#define MAXABITS 32  // Assuming MAXABITS is defined as 32

/*@ axiomatic Sum_array {
      logic integer sum(int* array, integer begin, integer end) reads array[begin .. (end-1)];
      axiom empty:
        \forall int* a, integer b, e; b >= e ==> sum(a,b,e) == 0;
      axiom range:
        \forall int* a, integer b, e; b < e ==> sum(a,b,e) == sum(a,b,e-1) + a[e-1];
    }
*/

/*@ 
  // Declare MAXABITS as a constant for ACSL
  axiomatic Constants {
    logic integer MAXABITS = 32;
  }
*/

/*@
  requires \valid(pIp) && \valid(pIp->t) && \valid(pIp->ct);
  requires pIp->t->asize >= 0;
  requires \valid(pIp->ct->nums + (0..MAXABITS));
  assigns pIp->ct->nums[0..MAXABITS], pIp->ct->total, pIp->ct->na;
  ensures pIp->ct->total == \old(pIp->ct->total) + sum(pIp->ct->nums, 0, MAXABITS + 1);
  ensures pIp->ct->na == \old(pIp->ct->na) + sum(pIp->ct->nums, 0, MAXABITS + 1);
*/
void numusearrayFun(numusearray *pIp) 
{
  int lg;
  unsigned int ttlg;  /* 2^lg */
  unsigned int ause = 0;  /* summation of 'nums' */
  unsigned int i = 1;  /* index to traverse all array keys */
  unsigned int asize = pIp -> t->asize;

  /*@ loop invariant 0 <= lg <= MAXABITS + 1;
      loop invariant ttlg == (lg == 0 ? 1 : 1 << (lg - 1));
      loop invariant 1 <= i <= asize + 1;
      loop invariant ause == sum(pIp->ct->nums, 0, lg);
      loop assigns lg, ttlg, ause, i, pIp->ct->nums[0..MAXABITS];
      loop variant MAXABITS - lg;
  */
  for (lg = 0, ttlg = 1; lg <= MAXABITS; lg++, ttlg *= 2) {
    unsigned int lc = 0;  /* counter */
    unsigned int lim = ttlg;
    if (lim > asize) {
      lim = asize;  /* adjust upper limit */
      if (i > lim)
        break;  /* no more elements to count */
    }

    /*@ loop invariant i <= lim + 1;
        loop invariant lc == (\forall integer j; i <= j <= lim ==> (pIp->t + j == NULL ? 1 : 0));
        loop assigns i, lc;
        loop variant lim - i;
    */
    for (; i <= lim; i++) {
      if (pIp -> t + i == NULL)
        lc++;
    }
    pIp -> ct->nums[lg] += lc;
    ause += lc;
  }
  pIp -> ct->total += ause;
  pIp -> ct->na += ause;
}
