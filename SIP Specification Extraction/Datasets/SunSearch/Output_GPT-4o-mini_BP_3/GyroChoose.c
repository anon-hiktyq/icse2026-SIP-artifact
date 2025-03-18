
#include "GyroChoose.h"

/* 
   @requires pIp != NULL && pIp->pGyroData != NULL;
   @ensures \forall integer j; 0 <= j < 9 ==> 
            (pIp->pGyroData->stateFlag[j] == TRUE ==> 
             (pIp->pGyroData->SignFlag[pIp->pGyroData->JoinTotal - 1] == j)) &&
            (pIp->pGyroData->stateFlag[j] == FALSE ==> 
             (\forall integer k; 0 <= k < pIp->pGyroData->JoinTotal ==> 
              pIp->pGyroData->SignFlag[k] != j));
   @ensures pIp->pGyroData->JoinTotal <= 9;
   @ensures pIp->pGyroData->gyroStatus0 == \bigvee_{j=0}^{8} (pIp->pGyroData->stateFlag[j] ? (1 << j) : 0);
   @ensures pIp->pGyroData->JoinTotal == \count{j}{0 <= j < 9 && pIp->pGyroData->stateFlag[j] == TRUE};
*/
void GyroChooseFun(GyroChoose *pIp)
{
    unint08 i;

    pIp->pGyroData->JoinTotal = 0;
    pIp->pGyroData->gyroStatus0 = 0;

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
