
#include "TripleFabsMax.h"

/*@ axiomatic FloatAbs {
      logic real float_abs(real x) = x < 0.0 ? -x : x;
    }
*/

/*@ axiomatic FloatMax {
      logic real float_max(real x, real y) = x > y ? x : y;
    }
*/

/*@ requires \valid(pIp);
    requires \valid(pIp->ret);
    assigns pIp->tmax, *(pIp->ret);
    ensures *(pIp->ret) == float_max(float_max(float_abs(pIp->fx1), float_abs(pIp->fy2)), float_abs(pIp->fz3));
    ensures pIp->tmax == float_max(float_max(float_abs(pIp->fx1), float_abs(pIp->fy2)), float_abs(pIp->fz3));
*/
void TripleFabsMaxFun(TripleFabsMax *pIp)
{
    float32 fabsfx1;
    float32 fabsfy2;
    float32 fabsfz3;

    /*@ assert \valid(pIp); */
    /*@ assert \valid(pIp->ret); */

    fabsfx1 = pIp->fx1;
    fabsfy2 = pIp->fy2;
    fabsfz3 = pIp->fz3;

    /*@ assert fabsfx1 == float_abs(pIp->fx1); */
    if (pIp->fx1 < 0.0f)
    {
        fabsfx1 = -pIp->fx1;
    }

    /*@ assert fabsfy2 == float_abs(pIp->fy2); */
    if (pIp->fy2 < 0.0f)
    {
        fabsfy2 = -pIp->fy2;
    }

    /*@ assert fabsfz3 == float_abs(pIp->fz3); */
    if (pIp->fz3 < 0.0f)
    {
        fabsfz3 = -pIp->fz3;
    }

    /*@ assert fabsfx1 == float_abs(pIp->fx1); */
    /*@ assert fabsfy2 == float_abs(pIp->fy2); */
    /*@ assert fabsfz3 == float_abs(pIp->fz3); */

    if (fabsfx1 > fabsfy2)
    {
        pIp->tmax = fabsfx1;
    }
    else
    {
        pIp->tmax = fabsfy2;
    }

    /*@ assert pIp->tmax == float_max(float_abs(pIp->fx1), float_abs(pIp->fy2)); */

    if (fabsfz3 > pIp->tmax)
    {
        pIp->tmax = fabsfz3;
    }

    /*@ assert pIp->tmax == float_max(float_max(float_abs(pIp->fx1), float_abs(pIp->fy2)), float_abs(pIp->fz3)); */

    *(pIp->ret) = pIp->tmax;
}
