
#include "LimitFloat32.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->ret);
  requires pIp->fbound > 0; // Assuming fbound must be positive for valid limits
  ensures \valid(pIp->ret);
  assigns pIp->fvalue, *(pIp->ret);
*/
void LimitFloat32Fun(LimitFloat32 *pIp)
{
    /*@ loop invariant \valid(pIp);
        loop assigns pIp->fvalue, *(pIp->ret);
    */
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
