
#include "ModPNHP.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->ret);
  requires \valid(pIp->halfperiod);
  requires \valid(pIp->x);
  ensures \valid(pIp->ret);
  assigns pIp->npp2, *(pIp->ret);
*/
void ModPNHPFun(ModPNHP *pIp)
{
    float32 period;

    period = 2.0f * pIp->halfperiod;

    /*@ loop invariant \valid(pIp->ret); 
    */
    pIp->npp2 = pIp->x - (pIp->x + pIp->halfperiod) / period * period;

    /*@ ensures \valid(pIp->ret);
        assigns *(pIp->ret); 
    */
    *(pIp->ret) = pIp->npp2;
}
