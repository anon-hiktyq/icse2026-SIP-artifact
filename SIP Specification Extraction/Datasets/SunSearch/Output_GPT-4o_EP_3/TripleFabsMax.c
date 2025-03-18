
#include "TripleFabsMax.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->ret);
  ensures *(pIp->ret) == \let abs_fx1 = (pIp->fx1 < 0.0f ? -pIp->fx1 : pIp->fx1);
                   \let abs_fy2 = (pIp->fy2 < 0.0f ? -pIp->fy2 : pIp->fy2);
                   \let abs_fz3 = (pIp->fz3 < 0.0f ? -pIp->fz3 : pIp->fz3);
                   \let max_fabs = (abs_fx1 > abs_fy2 ? abs_fx1 : abs_fy2);
                   (abs_fz3 > max_fabs ? abs_fz3 : max_fabs);
  assigns pIp->tmax, *(pIp->ret);
*/
void TripleFabsMaxFun(TripleFabsMax *pIp)
{
    float32 fabsfx1;
    float32 fabsfy2;
    float32 fabsfz3;

    fabsfx1 = pIp->fx1;
    fabsfy2 = pIp->fy2;
    fabsfz3 = pIp->fz3;

    if (pIp->fx1 < 0.0f)
    {
        fabsfx1 = -pIp->fx1;
    }

    if (pIp->fy2 < 0.0f)
    {
        fabsfy2 = -pIp->fy2;
    }

    if (pIp->fz3 < 0.0f)
    {
        fabsfz3 = -pIp->fz3;
    }

    if (fabsfx1 > fabsfy2)
    {
        pIp->tmax = fabsfx1;
    }
    else
    {
        pIp->tmax = fabsfy2;
    }

    if (fabsfz3 > pIp->tmax)
    {
        pIp->tmax = fabsfz3;
    }

    *(pIp->ret) = pIp->tmax;
}
