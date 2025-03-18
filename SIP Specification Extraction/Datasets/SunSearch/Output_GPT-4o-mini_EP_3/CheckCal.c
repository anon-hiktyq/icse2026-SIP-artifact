
#include "CheckCal.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->pkv + (0..pIp->len - 1));
  requires pIp->len >= 0;
  assigns \nothing;
*/
void CheckCalFun(CheckCal *pIp)
{
    /*@ loop invariant 0 <= i <= pIp->len;
        loop invariant chksum == sum(pIp->pkv, 0, i); 
        loop assigns chksum;
        loop variant pIp->len - i; 
    */
    unint32 chksum = 0; // Declare chksum as a local variable
    for(unint32 i = 0; i < pIp->len; i++)
    {
        /*@ requires \valid(pIp->pkv + i); */
        chksum = chksum + pIp->pkv[i];
    }

    return;
}
