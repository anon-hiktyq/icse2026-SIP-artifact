
#include "computesizes.h"

/*@ axiomatic ArrayXHash {
      logic boolean arrayXhash(int size, int elements);
    }
*/

/*@ axiomatic SumArray {
      logic int sum(int* array, int begin, int end) reads array[begin .. (end-1)];
      axiom empty:
        \forall int* a, int b, e; b >= e ==> sum(a,b,e) == 0;
      axiom range:
        \forall int* a, int b, e; b < e ==> sum(a,b,e) == sum(a,b,e-1) + a[e-1];
    }
*/

/*@
  requires \valid(pIp) && \valid(pIp->ct) && \valid(pIp->ret);
  requires \exists int i; \valid(pIp->ct->nums + (0..i));
  assigns pIp->optimal, pIp->ct->na, *(pIp->ret);
  ensures *(pIp->ret) == pIp->optimal;
  ensures pIp->ct->na == \old(pIp->ct->na) + a;
*/
void computesizesFun(computesizes *pIp) 
{
  int i;
  unsigned int twotoi;  /* 2^i (candidate for pIp -> optimal size) */
  unsigned int a = 0;  /* number of elements smaller than 2^i */
  unsigned int na = 0;  /* number of elements to go to array part */
  pIp -> optimal = 0; 

  /*@ loop invariant 0 <= i;
      loop invariant twotoi == 1 << i;
      loop invariant a == sum(pIp->ct->nums, 0, i);
      loop invariant na == sum(pIp->ct->nums, 0, i);
      loop invariant pIp->optimal == \max(0, sum(pIp->ct->nums, 0, i));
      loop assigns pIp->optimal, na, a, i, twotoi;
      loop variant INT_MAX - i;
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
