
#include "ModPNHP.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->ret);
  assigns pIp->npp2, *(pIp->ret);
  ensures *(pIp->ret) == pIp->npp2;
*/
void ModPNHPFun(ModPNHP *pIp)
{
    float32 period;

    /*@ 
      assigns period;
      ensures period == 2.0f * pIp->halfperiod;
    */
    period = 2.0f * pIp->halfperiod;

    /*@ 
      assigns pIp->npp2;
      ensures pIp->npp2 == pIp->x - (pIp->x + pIp->halfperiod) / period * period;
    */
    pIp -> npp2 = pIp -> x - (pIp -> x + pIp -> halfperiod) / period * period;

    /*@ 
      assigns *(pIp->ret);
      ensures *(pIp->ret) == pIp->npp2;
    */
    *(pIp -> ret) = pIp -> npp2;
}
