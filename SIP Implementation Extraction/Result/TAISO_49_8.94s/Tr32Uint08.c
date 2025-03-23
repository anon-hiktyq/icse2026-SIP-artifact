#include "Tr32Uint08.h"
void Tr32Uint08Fun(void *p) 
{
    Tr32Uint08 *pIp = (Tr32Uint08*)p;

    unint08 uitemp1 ;
    unint08 uitemp2 ;
    unint08 uitemp3 ;
    unint08 pIp -> uiresult ;

    if (((pIp -> *pA) == (pIp -> *pB)) && ((pIp -> *pA) == (pIp -> *pC)))
    {
        pIp -> uiresult = (pIp -> *pA) ;
    }
    else
    {
        uitemp1 = (pIp -> *pA) & (pIp -> *pB) ;
        uitemp2 = (pIp -> *pA) & (pIp -> *pC) ;
        uitemp3 = (pIp -> *pB) & (pIp -> *pC) ;
        pIp -> uiresult = uitemp1 | uitemp2 | uitemp3 ;

        pIp -> *pA = pIp -> uiresult ;
        pIp -> *pB = pIp -> uiresult ;
        pIp -> *pC = pIp -> uiresult ;
    }

    *(pIp -> ret) = uiresult ;
}