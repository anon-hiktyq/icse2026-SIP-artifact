
#include "LimitFloat32.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->ret);
  ensures pIp->fin > pIp->fbound ==> pIp->fvalue == pIp->fbound;
  ensures pIp->fin < -pIp->fbound ==> pIp->fvalue == -pIp->fbound;
  ensures -pIp->fbound <= pIp->fin <= pIp->fbound ==> pIp->fvalue == pIp->fin;
  ensures *(pIp->ret) == pIp->fvalue;
  assigns pIp->fvalue, *(pIp->ret);
*/
void LimitFloat32Fun(LimitFloat32 *pIp)
{
    if (pIp->fin > pIp->fbound)
    {
        pIp->fvalue = pIp->fbound;
    }
    else if (pIp->fin < -pIp->fbound)
    {
        pIp->fvalue = -pIp->fbound;
    }
    else
    {
        pIp->fvalue = pIp->fin;
    }

    *(pIp->ret) = pIp->fvalue;
}
