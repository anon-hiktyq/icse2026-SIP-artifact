
#include "CheckCal.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->pkv + (0 .. pIp->len-1));
  assigns \nothing;
*/
void CheckCalFun(CheckCal *pIp)
{
    unint32 i;
    unint08 chksum = 0;

    /*@ 
      loop invariant 0 <= i <= pIp->len;
      loop invariant chksum == \sum(pIp->pkv, 0, i);
      loop assigns i, chksum;
      loop variant pIp->len - i;
    */
    for(i = 0; i < pIp->len; i++)
    {
        chksum = chksum + pIp->pkv[i];
    }

    return;
}
