
#include "CheckCal16.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->pkv + (0 .. pIp->len-1));
  assigns \nothing;
*/
void CheckCal16Fun(CheckCal16 *pIp)
{
    unint32 i;
    unint16 chksum = 0;

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
