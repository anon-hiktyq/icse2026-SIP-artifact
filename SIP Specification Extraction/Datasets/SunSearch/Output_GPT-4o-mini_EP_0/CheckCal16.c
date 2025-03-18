
#include "CheckCal16.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->pkv + (0..pIp->len - 1));
  requires pIp->len >= 0;
  assigns \nothing;
*/
void CheckCal16Fun(CheckCal16 *pIp)
{
    /*@ loop invariant 0 <= i <= pIp->len;
        loop invariant chksum == \old(chksum) + \sum(pIp->pkv + (0..i-1));
        loop assigns chksum, i;
        loop variant pIp->len - i;
    */
    for(unint32 i = 0; i < pIp->len; i++)
    {
        chksum = chksum + pIp->pkv[i];
    }
    return;
}
