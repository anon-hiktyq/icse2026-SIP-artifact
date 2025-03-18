
#include "GyroPick.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->pGyroData);
  requires \valid(pIp->pGyroData->wa + (0..8));
  requires \valid(pIp->pGyroData->wal + (0..8));
  requires \valid(pIp->pGyroData->countPick + (0..8));
  assigns pIp->pGyroData->countPick[0..8], pIp->pGyroData->wa[0..8], pIp->pGyroData->wal[0..8];
*/
void GyroPickFun(GyroPick *pIp)
{
    /*@ loop invariant 0 <= iy <= 9;
        loop variant 9 - iy; 
    */
    for (unint08 iy = 0; iy < 9; iy++)
    {
        /*@ requires \valid(pIp->pGyroData->wa + (0..8));
            requires \valid(pIp->pGyroData->wal + (0..8));
            assigns tmpgi;
        */
        float32 tmpgi = ABS(pIp->pGyroData->wa[iy] - pIp->pGyroData->wal[iy]);

        /*@ requires tmpgi > 0.048f ==> \valid(pIp->pGyroData->countPick + (0..8));
            assigns pIp->pGyroData->countPick[iy];
        */
        if (tmpgi > 0.048f)
        {
            pIp->pGyroData->countPick[iy]++;

            /*@ requires pIp->pGyroData->countPick[iy] < 6;
                assigns pIp->pGyroData->wa[iy];
            */
            if (pIp->pGyroData->countPick[iy] < 6)
            {
                pIp->pGyroData->wa[iy] = pIp->pGyroData->wal[iy];
            }
            else
            {
                /*@ assigns pIp->pGyroData->wal[iy], pIp->pGyroData->countPick[iy];
                */
                pIp->pGyroData->wal[iy] = pIp->pGyroData->wa[iy];
                pIp->pGyroData->countPick[iy] = 0;
            }
        }
        else
        {
            /*@ assigns pIp->pGyroData->wal[iy], pIp->pGyroData->countPick[iy];
            */
            pIp->pGyroData->wal[iy] = pIp->pGyroData->wa[iy];
            pIp->pGyroData->countPick[iy] = 0;
        }
    }

    return;
}
