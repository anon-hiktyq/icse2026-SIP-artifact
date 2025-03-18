
#include "TripleFabsMax.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->ret);
  ensures \valid(pIp->ret);
  ensures *pIp->ret == \old(pIp->tmax);
  assigns pIp->tmax, *(pIp->ret);
*/
void TripleFabsMaxFun(TripleFabsMax *pIp)
{
    /*@ 
      requires \valid(pIp);
      assigns \nothing; // No assignments in this context
    */
    float32 fabsfx1;
    float32 fabsfy2;
    float32 fabfz3;

    fabsfx1 = pIp->fx1;
    fabsfy2 = pIp->fy2;
    fabfz3 = pIp->fz3;

    /*@ loop invariant fabsfx1 == (pIp->fx1 < 0.0f ? -pIp->fx1 : pIp->fx1);
        loop assigns \nothing; // No assignments in this context
    */
    if (pIp->fx1 < 0.0f)
    {
        fabsfx1 = -pIp->fx1;
    }

    /*@ loop invariant fabsfy2 == (pIp->fy2 < 0.0f ? -pIp->fy2 : pIp->fy2);
        loop assigns \nothing; // No assignments in this context
    */
    if (pIp->fy2 < 0.0f)
    {
        fabsfy2 = -pIp->fy2;
    }

    /*@ loop invariant fabfz3 == (pIp->fz3 < 0.0f ? -pIp->fz3 : pIp->fz3);
        loop assigns \nothing; // No assignments in this context
    */
    if (pIp->fz3 < 0.0f)
    {
        fabfz3 = -pIp->fz3;
    }

    /*@ loop invariant pIp->tmax == (fabsfx1 > fabsfy2 ? fabsfx1 : fabsfy2);
        loop assigns pIp->tmax; // This is valid as tmax is being assigned
    */
    if (fabsfx1 > fabsfy2)
    {
        pIp->tmax = fabsfx1;
    }
    else
    {
        pIp->tmax = fabsfy2;
    }

    /*@ loop invariant pIp->tmax >= fabfz3 || fabfz3 >= pIp->tmax;
        loop assigns pIp->tmax; // This is valid as tmax is being assigned
    */
    if (fabsfz3 > pIp->tmax)
    {
        pIp->tmax = fabfz3;
    }

    /*@ requires \valid(pIp->ret);
      assigns *(pIp->ret);
    */
    *(pIp->ret) = pIp->tmax;
}
