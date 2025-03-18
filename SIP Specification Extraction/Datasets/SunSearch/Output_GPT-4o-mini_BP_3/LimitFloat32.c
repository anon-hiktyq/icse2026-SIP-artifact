
#include "LimitFloat32.h"

/*@ 
    requires pIp != \null; 
    requires \valid(pIp);
    requires \valid(pIp->ret);
    requires \valid(pIp->fbound);
    requires \valid(pIp->fin);
    assigns pIp->fvalue, *(pIp->ret);
    ensures pIp->fvalue == (pIp->fin > pIp->fbound ? pIp->fbound :
                            (pIp->fin < -pIp->fbound ? -pIp->fbound : pIp->fin));
    ensures *(pIp->ret) == pIp->fvalue;
*/
void LimitFloat32Fun(LimitFloat32 *pIp)
{
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

    *(pIp -> ret) = pIp -> fvalue ;
}
