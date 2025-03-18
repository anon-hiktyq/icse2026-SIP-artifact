
#include "GyroChoose.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->pGyroData);
  requires \valid(pIp->pGyroData->stateFlag + (0..8));
  requires \valid(pIp->pGyroData->SignFlag + (0..8));
  requires 0 <= pIp->pGyroData->JoinTotal <= 9;
  assigns pIp->pGyroData->JoinTotal;
  assigns pIp->pGyroData->gyroStatus0;
  assigns pIp->pGyroData->SignFlag[0..8];
*/
void GyroChooseFun(GyroChoose *pIp)
{
    unint08 i;

    pIp->pGyroData->JoinTotal = 0;
    pIp->pGyroData->gyroStatus0 = 0;

    /*@ 
      loop invariant 0 <= i <= 9;
      loop invariant 0 <= pIp->pGyroData->JoinTotal <= i;
      loop invariant \forall integer k; 0 <= k < i ==> 
          (pIp->pGyroData->stateFlag[k] == TRUE ==> 
           pIp->pGyroData->SignFlag[pIp->pGyroData->JoinTotal - 1] == k);
      loop assigns i, pIp->pGyroData->JoinTotal, pIp->pGyroData->gyroStatus0, pIp->pGyroData->SignFlag[0..8];
      loop variant 9 - i;
    */
    for (i = 0; i < 9; i++)
    {
        if (pIp->pGyroData->stateFlag[i] == TRUE)
        {
            pIp->pGyroData->SignFlag[pIp->pGyroData->JoinTotal] = i;
            pIp->pGyroData->JoinTotal++;
            pIp->pGyroData->gyroStatus0 = pIp->pGyroData->gyroStatus0 | (1 << i);
        }
    }

    return;
}
