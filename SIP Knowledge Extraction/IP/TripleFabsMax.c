#include "TripleFabsMax.h"
void TripleFabsMaxFun(void *p)
{
    TripleFabsMax *pIp = (TripleFabsMax*)p;

    float32 fabsfx1 ;
    float32 fabsfy2 ;
    float32 fabsfz3 ;
 

    fabsfx1 = pIp -> fx1;
    fabsfy2 = pIp -> fy2;
    fabsfz3 = pIp -> fz3;

    if (pIp -> fx1 < 0.0f)
    {
        fabsfx1 = -pIp -> fx1;
    }

    if (pIp -> fy2 < 0.0f)
    {
        fabsfy2 = -pIp -> fy2;
    }

    if (pIp -> fz3 < 0.0f)
    {
        fabsfz3 = -pIp -> fz3;
    }

    if (fabsfx1 > fabsfy2)
    {
        pIp -> tmax = fabsfx1 ;
    }
    else
    {
        pIp -> tmax = fabsfy2 ;
    }

    if (fabsfz3 > pIp -> tmax)
    {
        pIp -> tmax = fabsfz3 ;
    }

    *(pIp -> ret) = pIp->tmax ;
}