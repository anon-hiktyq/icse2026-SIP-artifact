
#include "Delay.h"

/*@ axiomatic Delay {
      logic integer sum(int* array, integer begin, integer end) reads array[begin .. (end-1)];
      axiom empty:
      \forall int* a, integer b, e; b >= e ==> sum(a,b,e) == 0;
      axiom range:
      \forall int* a, integer b, e; b < e ==> sum(a,b,e) == sum(a,b,e-1) + a[e-1];
   }
*/

/*@ requires \valid(pIp);
    requires \valid(&pIp->delaytime);
    ensures \result == \old(pIp->delaytime);
    assigns \nothing;
*/
void DelayFun(Delay *pIp)
{
    unint16 uidt;

    /*@ loop invariant 0 <= uidt <= pIp->delaytime;
        loop assigns uidt;
        loop variant pIp->delaytime - uidt;
    */
    for (uidt = 0; uidt < pIp->delaytime; uidt++)
    {
        ;
    }

    return;
}
