
#include "computesizes.h"

/*@ axiomatic ArrayXhash {
      logic boolean arrayXhash(int size, int count);
    }
*/

/*@ axiomatic SumArray {
      logic integer sum(integer* array, integer begin, integer end) reads array[begin .. (end-1)];
      axiom sum_empty:
        \forall integer* a, integer b, e; b >= e ==> sum(a, b, e) == 0;
      axiom sum_range:
        \forall integer* a, integer b, e; b < e ==> sum(a, b, e) == sum(a, b, e-1) + a[e-1];
    }
*/

/*@ axiomatic Max {
      logic integer max(integer x, integer y);
      axiom max_def:
        \forall integer x, y; (x >= y ==> max(x, y) == x) && (x < y ==> max(x, y) == y);
    }
*/

/*@
  requires \valid(pIp);
  requires \valid(pIp->ct);
  requires \valid(pIp->ct->nums + (0..MAX_SLICES-1));
  requires \valid(pIp->ret);
  assigns pIp->optimal, pIp->ct->na, *pIp->ret;
  ensures pIp->optimal == \old(pIp->optimal) || pIp->optimal > \old(pIp->optimal);
  ensures *pIp->ret == pIp->optimal;
*/
void computesizesFun(computesizes *pIp) 
{
  int i;
  unsigned int twotoi;  /* 2^i (candidate for pIp -> optimal size) */
  unsigned int a = 0;  /* number of elements smaller than 2^i */
  unsigned int na = 0;  /* number of elements to go to array part */
  pIp -> optimal = 0; 

  /*@ loop invariant 0 <= i <= MAX_SLICES;
      loop invariant twotoi == (i == 0 ? 1 : \at(twotoi, Pre) * (1 << i));
      loop invariant a == sum((integer*)pIp->ct->nums, 0, i);
      loop invariant na == max(sum((integer*)pIp->ct->nums, 0, i), na);
      loop invariant pIp->optimal == max(\at(pIp->optimal, Pre), twotoi);
      loop assigns i, twotoi, a, na, pIp->optimal;
      loop variant MAX_SLICES - i;
  */
  for (i = 0, twotoi = 1;
       twotoi > 0 && arrayXhash(twotoi, pIp -> ct->na);
       i++, twotoi *= 2) {
    unsigned nums = pIp -> ct->nums[i];
    a += nums;
    if (nums > 0 &&  /* grows array only if it gets more elements... */
        arrayXhash(twotoi, a)) {  /* ...while using "less memory" */
      pIp -> optimal = twotoi;  /* pIp -> optimal size (till now) */
      na = a;  /* all elements up to 'pIp -> optimal' will go to array part */
    }
  }
  pIp -> ct->na = na;
  *(pIp -> ret) = pIp->optimal;
}
