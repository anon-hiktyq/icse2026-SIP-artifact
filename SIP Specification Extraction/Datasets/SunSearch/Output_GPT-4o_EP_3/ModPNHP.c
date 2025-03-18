
#include "ModPNHP.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->ret);
  ensures *(pIp->ret) == pIp->npp2;
  assigns pIp->npp2, *(pIp->ret);
*/
void ModPNHPFun(ModPNHP *pIp)
{
    float32 period;

    period = 2.0f * pIp->halfperiod;

    /*@
      requires period != 0;
      ensures pIp->npp2 == pIp->x - (pIp->x + pIp->halfperiod) / period * period;
      assigns pIp->npp2;
    */
    pIp->npp2 = pIp->x - (pIp->x + pIp->halfperiod) / period * period;

    *(pIp->ret) = pIp->npp2;
}
