
#include "MatrixMulti.h"
#include "CalculateGyroDg.h"
#include "MatrixMulti.h"

/*@ 
  requires pIp != NULL;
  requires pIp->pGyroData != NULL;
  requires \valid(pIp->pGyroData->SignFlag + (0..pIp->pGyroData->JoinTotal - 1));
  requires \valid(pIp->pGyroData->wa + (0..MAX_WA_INDEX)); // Assuming MAX_WA_INDEX is defined
  requires \valid(pIp->pGyroData->W + (0..2));
  requires \valid(pIp->pGyroData->Rtemp + (0..2)(0..4));
  ensures pIp->pGyroData->W[0] == (pIp->pGyroData->JoinTotal >= 3 ? \result : 0.0f);
  ensures pIp->pGyroData->W[1] == (pIp->pGyroData->JoinTotal >= 3 ? \result : 0.0f);
  ensures pIp->pGyroData->W[2] == (pIp->pGyroData->JoinTotal >= 3 ? \result : 0.0f);
*/
void CalculateGyroDgFun(CalculateGyroDg *pIp)
{
    /*@
      loop invariant 0 <= j <= 5;
      loop assigns tmpwa[0..4];
    */
    for (unint08 j = 0; j < 5; j++)
    {
        tmpwa[j] = 0;
    }

    /*@
      loop invariant 0 <= j <= pIp->pGyroData->JoinTotal;
      loop assigns tmpwa[0..pIp->pGyroData->JoinTotal - 1];
      loop variant pIp->pGyroData->JoinTotal - j;
    */
    for (j = 0; j < pIp->pGyroData->JoinTotal; j++)
    {
        unint08 k = pIp->pGyroData->SignFlag[j];
        tmpwa[j] = pIp->pGyroData->wa[k];
    }

    /*@
      requires pIp->pGyroData->JoinTotal >= 3 ==> \valid(pIp->pGyroData->W + (0..2));
    */
    if (pIp->pGyroData->JoinTotal >= 3)
    {
        IPCREATE(MatrixMulti, ipMatrixMulti, .product = &(pIp->pGyroData->W[0]), .faciend = &(pIp->pGyroData->Rtemp[0][0]), .multiplier = &tmpwa[0], .nrow = 3, .nrc = 5, .ncol = 1);
        IPCALL(ipMatrixMulti);
    }
    else
    {
        pIp->pGyroData->W[0] = 0.0f;
        pIp->pGyroData->W[1] = 0.0f;
        pIp->pGyroData->W[2] = 0.0f;
    }

    return;
}
