
#include "GyroPick.h"

/*@ axiomatic GyroPickLogic {
      logic real abs_diff(real x, real y) = x > y ? x - y : y - x;
    }
*/

/*@ requires \valid(pIp);
    requires \valid(pIp->pGyroData);
    requires \valid(pIp->pGyroData->wa + (0..8));
    requires \valid(pIp->pGyroData->wal + (0..8));
    requires \valid(pIp->pGyroData->countPick + (0..8));
    assigns pIp->pGyroData->wa[0..8];
    assigns pIp->pGyroData->wal[0..8];
    assigns pIp->pGyroData->countPick[0..8];
*/
void GyroPickFun(GyroPick *pIp)
{
    unint08 iy;
    float32 tmpgi;

    /*@ loop invariant 0 <= iy <= 9;
        loop invariant \forall integer k; 0 <= k < iy ==> 
            pIp->pGyroData->countPick[k] == \at(pIp->pGyroData->countPick[k], Pre) + 
            (abs_diff(pIp->pGyroData->wa[k], pIp->pGyroData->wal[k]) > 0.048f ? 1 : 0);
        loop assigns iy, tmpgi, pIp->pGyroData->wa[0..8], pIp->pGyroData->wal[0..8], pIp->pGyroData->countPick[0..8];
        loop variant 9 - iy;
    */
    for (iy = 0; iy < 9; iy++)
    {
        tmpgi = ABS(pIp->pGyroData->wa[iy] - pIp->pGyroData->wal[iy]);

        if (tmpgi > 0.048f)
        {
            pIp->pGyroData->countPick[iy]++;

            if (pIp->pGyroData->countPick[iy] < 6)
            {
                pIp->pGyroData->wa[iy] = pIp->pGyroData->wal[iy];
            }
            else
            {
                pIp->pGyroData->wal[iy] = pIp->pGyroData->wa[iy];
                pIp->pGyroData->countPick[iy] = 0;
            }
        }
        else
        {
            pIp->pGyroData->wal[iy] = pIp->pGyroData->wa[iy];
            pIp->pGyroData->countPick[iy] = 0;
        }
    }

    return;
}
