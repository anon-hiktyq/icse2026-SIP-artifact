
#include "CheckCal.h"

/*@ 
  requires pIp != NULL; 
  requires \valid(pIp);
  requires \valid(pIp->pkv + (0..pIp->len - 1)); 
  requires pIp->len >= 0; 
  ensures \result == \nothing; 
*/
void CheckCalFun(CheckCal *pIp)
{
    /*@
      loop invariant 0 <= i <= pIp->len;
      loop invariant chksum == \sum_{j=0}^{i-1} pIp->pkv[j];
      loop assigns chksum, i;
      loop variant pIp->len - i;
    */
    unsigned int i; // Changed from unint32 to unsigned int
    unsigned char chksum = 0; // Changed from unint08 to unsigned char

    for(i = 0; i < pIp -> len; i++)
    {
        chksum = chksum + pIp -> pkv[i];
    }

    return;
}
