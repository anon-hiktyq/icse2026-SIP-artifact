#include "LimitFloat32.h"
void LimitFloat32Fun(void *p) 
{
    LimitFloat32 *pIp = (LimitFloat32*)p;

    float32 pIp -> fvalue ;

    if (pIp -> fin > pIp -> fbound)
    {
        pIp -> fvalue = pIp -> fbound ;
    }
    else if (pIp -> fin < -pIp -> fbound)
    {
        pIp -> fvalue = -pIp -> fbound ;
    }
    else
    {
        pIp -> fvalue = pIp -> fin ;
    }

    *(pIp -> ret) = fvalue ;
}