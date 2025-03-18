
#include "numusearray.h"

/*@ axiomatic PowerOfTwo {
      logic int power_of_two(int n) = n == 0 ? 1 : 2 * power_of_two(n - 1);
    }
*/

/*@
  requires \valid(pIp) && \valid(pIp->t) && \valid(pIp->ct);
  requires pIp->t->asize >= 0;
  requires \forall int lg; 0 <= lg <= MAXABITS ==> \valid(pIp->ct->nums + lg);
  assigns pIp->ct->nums[0..MAXABITS], pIp->ct->total, pIp->ct->na;
  ensures pIp->ct->total == \old(pIp->ct->total) + (\sum int lg; 0 <= lg <= MAXABITS; pIp->ct->nums[lg]);
  ensures pIp->ct->na == \old(pIp->ct->na) + (\sum int lg; 0 <= lg <= MAXABITS; pIp->ct->nums[lg]);
*/
void numusearrayFun(numusearray *pIp) 
{
  int lg;
  unsigned int ttlg;  /* 2^lg */
  unsigned int ause = 0;  /* summation of 'nums' */
  unsigned int i = 1;  /* index to traverse all array keys */
  unsigned int asize = pIp -> t->asize;

  /*@ loop invariant 0 <= lg <= MAXABITS + 1;
      loop invariant ttlg == power_of_two(lg);
      loop invariant 1 <= i <= asize + 1;
      loop invariant ause == (\sum int k; 0 <= k < lg; pIp->ct->nums[k]);
      loop assigns lg, ttlg, i, ause, pIp->ct->nums[0..MAXABITS];
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
        loop invariant lc == (\sum int k; i <= k < lim; pIp->t + k == NULL ? 1 : 0);
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
