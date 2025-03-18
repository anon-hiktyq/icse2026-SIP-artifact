
#include "GyroPick.h"

/*@ 
  requires pIp != NULL;
  requires \valid(pIp->pGyroData);
  requires \valid(pIp->pGyroData->wa + (0..8));
  requires \valid(pIp->pGyroData->wal + (0..8));
  requires \valid(pIp->pGyroData->countPick + (0..8));
  assigns pIp->pGyroData->wa[0..8], pIp->pGyroData->wal[0..8], pIp->pGyroData->countPick[0..8];
  ensures \forall integer i; 0 <= i < 9 ==> 
    (pIp->pGyroData->countPick[i] >= 0 && pIp->pGyroData->countPick[i] <= 5) || 
    (pIp->pGyroData->countPick[i] == 0 && pIp->pGyroData->wal[i] == pIp->pGyroData->wa[i]);
*/

void GyroPickFun(GyroPick *pIp)
{
    unint08 iy;
    float32 tmpgi;

    /*@
      loop invariant 0 <= iy <= 9;
      loop assigns iy, tmpgi, pIp->pGyroData->wa[0..8], pIp->pGyroData->wal[0..8], pIp->pGyroData->countPick[0..8];
      loop variant 9 - iy;
    */
    for (iy = 0; iy < 9; iy++)
    {
        /*@ 
          assigns tmpgi;
          loop invariant 0 <= iy < 9;
        */
        tmpgi = ABS(pIp->pGyroData->wa[iy] - pIp->pGyroData->wal[iy]);

        /*@
          assert pIp->pGyroData->countPick[iy] >= 0;
        */
        if (tmpgi > 0.048f)
        {
            pIp->pGyroData->countPick[iy]++;

            /*@ 
              assert pIp->pGyroData->countPick[iy] >= 1;
            */
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
