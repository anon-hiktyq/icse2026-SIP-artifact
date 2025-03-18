
#include "CheckCal16.h"

/*@ 
  requires pIp != NULL; 
  requires \valid(pIp); 
  requires \valid(pIp->pkv + (0..pIp->len - 1)); 
  requires pIp->len >= 0; 
  assigns \nothing; 
  ensures \result == \nothing; 
*/
void CheckCal16Fun(CheckCal16 *pIp)
{
    /*@ 
      loop invariant 0 <= i <= pIp->len; 
      loop invariant chksum == \sum_{j=0}^{i-1} pIp->pkv[j]; 
      loop assigns chksum, i; 
      loop variant pIp->len - i; 
    */
    unsigned int i; // corrected 'unint32' to 'unsigned int'
    unsigned short chksum = 0; // corrected 'unint16' to 'unsigned short'
    for(i = 0; i < pIp->len; i++)
    {
        chksum = chksum + pIp->pkv[i];
    }
    return;
}
