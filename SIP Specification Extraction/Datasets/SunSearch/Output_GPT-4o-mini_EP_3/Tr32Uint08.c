
#include "Tr32Uint08.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->pA) && \valid(pIp->pB) && \valid(pIp->pC) && \valid(pIp->ret);
  assigns pIp->uiresult, *(pIp->pA), *(pIp->pB), *(pIp->pC), *(pIp->ret);
*/
void Tr32Uint08Fun(Tr32Uint08 *pIp)
{
    unint08 uitemp1;
    unint08 uitemp2;
    unint08 uitemp3;

    if ((*(pIp->pA) == *(pIp->pB)) && (*(pIp->pA) == *(pIp->pC)))
    {
        pIp->uiresult = *(pIp->pA);
    }
    else
    {
        uitemp1 = *(pIp->pA) & *(pIp->pB);
        uitemp2 = *(pIp->pA) & *(pIp->pC);
        uitemp3 = *(pIp->pB) & *(pIp->pC);
        pIp->uiresult = uitemp1 | uitemp2 | uitemp3;

        *(pIp->pA) = pIp->uiresult;
        *(pIp->pB) = pIp->uiresult;
        *(pIp->pC) = pIp->uiresult;
    }

    *(pIp->ret) = pIp->uiresult;
}
