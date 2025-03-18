
#include "ModPNHP.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->ret);
  requires \valid(pIp->halfperiod);
  ensures \valid(pIp->ret);
  assigns pIp->npp2, *(pIp->ret);
*/
void ModPNHPFun(ModPNHP *pIp)
{
    /*@ 
      requires \valid(pIp);
      requires \valid(pIp->halfperiod);
      ensures period == 2.0f * pIp->halfperiod;
      assigns period;
    */
    float32 period;

    period = 2.0f * pIp->halfperiod;

    /*@ 
      requires \valid(pIp);
      requires \valid(pIp->ret);
      ensures pIp->npp2 == pIp->x - (pIp->x + pIp->halfperiod) / period * period;
      assigns pIp->npp2;
    */
    pIp->npp2 = pIp->x - (pIp->x + pIp->halfperiod) / period * period;

    /*@ 
      requires \valid(pIp);
      requires \valid(pIp->ret);
      ensures *(pIp->ret) == pIp->npp2;
      assigns *(pIp->ret);
    */
    *(pIp->ret) = pIp->npp2;
}
