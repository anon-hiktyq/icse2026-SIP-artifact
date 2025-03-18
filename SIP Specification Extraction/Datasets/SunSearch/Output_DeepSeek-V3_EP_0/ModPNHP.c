
#include "ModPNHP.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->ret);
  assigns *(pIp->ret);
  ensures *(pIp->ret) == \old(pIp->x) - (\old(pIp->x) + \old(pIp->halfperiod)) / (2.0f * \old(pIp->halfperiod)) * (2.0f * \old(pIp->halfperiod));
*/
void ModPNHPFun(ModPNHP *pIp)
{
    float32 period;

    /*@ assert \valid(pIp) && \valid(pIp->ret); */
    period = 2.0f * pIp->halfperiod;

    /*@ assert period == 2.0f * \old(pIp->halfperiod); */
    pIp->npp2 = pIp->x - (pIp->x + pIp->halfperiod) / period * period;

    /*@ assert pIp->npp2 == \old(pIp->x) - (\old(pIp->x) + \old(pIp->halfperiod)) / period * period; */
    *(pIp->ret) = pIp->npp2;
}
