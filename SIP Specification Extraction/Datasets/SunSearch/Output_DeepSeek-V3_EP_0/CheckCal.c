
#include "CheckCal.h"

/*@ axiomatic Sum_array {
      logic integer sum(int* array, integer begin, integer end) reads array[begin .. (end-1)];
      axiom empty:
        \forall int* a, integer b, e; b >= e ==> sum(a,b,e) == 0;
      axiom range:
        \forall int* a, integer b, e; b < e ==> sum(a,b,e) == sum(a,b,e-1) + a[e-1];
    }
*/

/*@ requires \valid(pIp);
    requires \valid(pIp->pkv + (0 .. pIp->len-1));
    assigns \nothing;
*/
void CheckCalFun(CheckCal *pIp)
{
    unint32 i;
    unint08 chksum = 0;

    /*@ loop invariant 0 <= i <= pIp->len;
        loop invariant chksum == sum(pIp->pkv, 0, i);
        loop assigns chksum, i;
        loop variant pIp->len - i;
    */
    for(i=0; i<pIp -> len; i++)
    {
        chksum = chksum + pIp -> pkv[i];
    }

    return;
}
