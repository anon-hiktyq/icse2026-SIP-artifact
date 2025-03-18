
#include "PseudoRateModulator.h"

/*@ 
requires \valid(pIp);
requires \valid(pIp->pModulator);
assigns pIp->pModulator->Yp, pIp->pModulator->Yn, pIp->pModulator->r;
*/
void PseudoRateModulatorFun(PseudoRateModulator *pIp)
{
    /*@ 
    requires \valid(pIp);
    requires \valid(pIp->pModulator);
    assigns pIp->pModulator->Yp, pIp->pModulator->Yn, pIp->pModulator->r;
    */
    if ((pIp->pModulator->u - pIp->pModulator->r) > pIp->h1)
    {
        pIp->pModulator->Yp = 0x0;
        pIp->pModulator->Yn = 0xF;
        pIp->pModulator->r = 0.9231f * pIp->pModulator->r + 0.07688f;
    }
    /*@ 
    requires \valid(pIp);
    requires \valid(pIp->pModulator);
    assigns pIp->pModulator->Yp, pIp->pModulator->Yn, pIp->pModulator->r;
    */
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
