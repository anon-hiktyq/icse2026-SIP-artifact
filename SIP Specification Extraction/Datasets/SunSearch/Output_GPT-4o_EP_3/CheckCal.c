
#include "CheckCal.h"

/*@ axiomatic Sum_array {
      logic integer sum{L}(unint08* array, integer begin, integer end) reads array[begin .. end-1];
      axiom empty{L}:
        \forall unint08* a, integer b, e; b >= e ==> sum(a, b, e) == 0;
      axiom range{L}:
        \forall unint08* a, integer b, e; b < e ==> sum(a, b, e) == sum(a, b, e-1) + a[e-1];
    }
*/

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->pkv + (0 .. pIp->len - 1));
  assigns pIp->pkv[0 .. pIp->len - 1];
  ensures \forall integer i; 0 <= i < pIp->len ==> pIp->pkv[i] == \old(pIp->pkv[i]);
*/
void CheckCalFun(CheckCal *pIp)
{
    unint32 i;
    unint08 chksum = 0;

    /*@ loop invariant 0 <= i <= pIp->len;
        loop invariant chksum == sum(pIp->pkv, 0, i);
        loop assigns i, chksum;
        loop variant pIp->len - i;
    */
    for(i = 0; i < pIp->len; i++)
    {
        chksum = chksum + pIp->pkv[i];
    }

    return;
}
