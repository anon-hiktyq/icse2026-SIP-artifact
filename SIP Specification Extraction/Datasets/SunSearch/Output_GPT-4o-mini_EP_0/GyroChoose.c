
#include "GyroChoose.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->pGyroData);
  requires \valid(pIp->pGyroData->stateFlag + (0..8));
  requires \valid(pIp->pGyroData->SignFlag + (0..8));
  ensures pIp->pGyroData->JoinTotal == \old(pIp->pGyroData->JoinTotal) + 
          \sum(int i; 0 <= i < 9 && pIp->pGyroData->stateFlag[i] == TRUE; 1);
  ensures pIp->pGyroData->gyroStatus0 == \old(pIp->pGyroData->gyroStatus0) | 
          \sum(int i; 0 <= i < 9 && pIp->pGyroData->stateFlag[i] == TRUE; (1 << i));
  assigns pIp->pGyroData->JoinTotal, pIp->pGyroData->gyroStatus0, 
          pIp->pGyroData->SignFlag[0..8];
*/
void GyroChooseFun(GyroChoose *pIp)
{
    unint08 i;

    pIp->pGyroData->JoinTotal = 0;
    pIp->pGyroData->gyroStatus0 = 0;

    /*@
      loop invariant 0 <= i <= 9;
      loop assigns pIp->pGyroData->JoinTotal, pIp->pGyroData->gyroStatus0, 
                   pIp->pGyroData->SignFlag[0..8];
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
