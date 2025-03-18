
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
        loop assigns chksum;
        loop variant pIp->len - i;
    */
    for(unint32 i = 0; i < pIp->len; i++)
    {
        chksum = chksum + pIp->pkv[i];
    }

    return;
}
