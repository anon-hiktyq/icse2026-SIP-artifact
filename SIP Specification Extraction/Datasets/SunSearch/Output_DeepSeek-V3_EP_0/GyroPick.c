
#include "GyroPick.h"

/*@ axiomatic GyroPickLogic {
      logic integer sum(int* array, integer begin, integer end) reads array[begin .. (end-1)];
      axiom empty:
        \forall int* a, integer b, e; b >= e ==> sum(a,b,e) == 0;
      axiom range:
        \forall int* a, integer b, e; b < e ==> sum(a,b,e) == sum(a,b,e-1) + a[e-1];
    }
*/

/*@ requires \valid(pIp);
    requires \valid(pIp->pGyroData);
    requires \valid(pIp->pGyroData->wa + (0..8));
    requires \valid(pIp->pGyroData->wal + (0..8));
    requires \valid(pIp->pGyroData->countPick + (0..8));
    assigns pIp->pGyroData->wa[0..8], pIp->pGyroData->wal[0..8], pIp->pGyroData->countPick[0..8];
*/
void GyroPickFun(GyroPick *pIp)
{
    unint08 iy;
    float32 tmpgi;

    /*@ loop invariant 0 <= iy <= 9;
        loop invariant \forall integer j; 0 <= j < iy ==> 
            pIp->pGyroData->countPick[j] == \at(pIp->pGyroData->countPick[j], Pre) + 
            (ABS(pIp->pGyroData->wa[j] - pIp->pGyroData->wal[j]) > 0.048f ? 1 : 0);
        loop assigns pIp->pGyroData->wa[0..8], pIp->pGyroData->wal[0..8], pIp->pGyroData->countPick[0..8];
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
