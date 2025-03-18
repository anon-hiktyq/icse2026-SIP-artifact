
#include "LimitFloat32.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->ret);
  ensures *pIp->ret == \old(pIp->fvalue) || 
          *pIp->ret == \old(pIp->fbound) || 
          *pIp->ret == -\old(pIp->fbound);
  assigns pIp->fvalue, *pIp->ret;
*/
void LimitFloat32Fun(LimitFloat32 *pIp)
{
    /*@ 
      assert \valid(pIp) && \valid(pIp->ret);
    */

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
