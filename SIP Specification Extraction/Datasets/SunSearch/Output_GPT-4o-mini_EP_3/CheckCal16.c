
#include "CheckCal16.h"

/*@ 
  requires \valid(pIp); 
  requires \valid(pIp->pkv + (0..pIp->len - 1)); 
  requires pIp->len > 0; 
  assigns pIp->pkv[0..pIp->len - 1]; 
*/
void CheckCal16Fun(CheckCal16 *pIp)
{
    /*@ loop invariant 0 <= i <= pIp->len; 
        loop invariant \forall int j; 0 <= j < i ==> 
            chksum == \old(chksum) + pIp->pkv[j]; 
        loop assigns chksum; 
        loop variant pIp->len - i; 
    */
    unint32 chksum = 0; // Declare chksum before the loop
    for(unint32 i = 0; i < pIp->len; i++)
    {
        chksum = chksum + pIp->pkv[i];
    }
    return;
}
