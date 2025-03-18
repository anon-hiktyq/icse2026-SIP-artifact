
#include "ModPNHP.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->ret);
  ensures *pIp->ret == \old(pIp->npp2);
  assigns *pIp->ret, pIp->npp2;
*/
void ModPNHPFun(ModPNHP *pIp)
{
    float32 period;

    /*@ assert \valid(pIp) && \valid(pIp->ret); */

    period = 2.0f * pIp->halfperiod;

    /*@ assert \valid(pIp) && \valid(pIp->ret); */

    pIp->npp2 = pIp->x - (pIp->x + pIp->halfperiod) / period * period;

    /*@ assert \valid(pIp->ret); */
    *(pIp->ret) = pIp->npp2;
}
