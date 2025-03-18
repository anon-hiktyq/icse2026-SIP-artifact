
#include "PseudoRateModulator.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->pModulator);
  requires \valid(pIp->pModulator->u);
  requires \valid(pIp->pModulator->r);
  requires \valid(pIp->pModulator->Yp);
  requires \valid(pIp->pModulator->Yn);
  requires lower_bound <= pIp->h1 <= upper_bound; // Assuming bounds for h1
  assigns pIp->pModulator->Yp, pIp->pModulator->Yn, pIp->pModulator->r;
*/
void PseudoRateModulatorFun(PseudoRateModulator *pIp)
{
    /*@ loop invariant \valid(pIp);
        loop assigns pIp->pModulator->Yp, pIp->pModulator->Yn, pIp->pModulator->r; 
    */
    if ((pIp->pModulator->u - pIp->pModulator->r) > pIp->h1)
    {
        pIp->pModulator->Yp = 0x0;
        pIp->pModulator->Yn = 0xF;
        pIp->pModulator->r = 0.9231f * pIp->pModulator->r + 0.07688f;
    }
    else if ((pIp->pModulator->u - pIp->pModulator->r) < -pIp->h1)
    {
        pIp->pModulator->Yp = 0xF;
        pIp->pModulator->Yn = 0x0;
        pIp->pModulator->r = 0.9231f * pIp->pModulator->r - 0.07688f;
    }
    else
    {
        pIp->pModulator->Yp = 0x0;
        pIp->pModulator->Yn = 0x0;
        pIp->pModulator->r = 0.9231f * pIp->pModulator->r;
    }

    return;
}
