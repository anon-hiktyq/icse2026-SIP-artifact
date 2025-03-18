
#include "MatrixInv33F.h"
#include "MatrixTran.h"
#include "MatrixMulti.h"
#include "CalculateGyroRs.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->pGyroData);
  requires \valid(pIp->pGyroData->SignFlag + (0..pIp->pGyroData->JoinTotal - 1));
  requires 0 <= pIp->pGyroData->JoinTotal <= 5;
  ensures pIp->pGyroData->gyroStatus1 == pIp->pGyroData->gyroStatus0;
  assigns pIp->flgGryoCalc, pIp->pGyroData->JoinTotal, 
          pIp->pGyroData->gyroStatus1, pIp->pGyroData->Rtemp[0..2][0..4]; // Specify the range for Rtemp
*/
void CalculateGyroRsFun(CalculateGyroRs *pIp)
{
    unint08 i;
    unint08 j;
    unint08 k;
    float32 Rgtrans[3][5];
    float32 Rs[3][3];
    float32 RsInv[3][3];
    float32 Rgtemp[5][3];

    pIp->pGyroData->JoinTotal = MIN(pIp->pGyroData->JoinTotal, 5);

    if (pIp->pGyroData->gyroStatus0 != pIp->pGyroData->gyroStatus1)
    {
        pIp->flgGryoCalc = TRUE;

        /*@ loop invariant 0 <= j <= pIp->pGyroData->JoinTotal;
            loop assigns Rgtemp[j][..];
            loop variant pIp->pGyroData->JoinTotal - j;
        */
        for (j = 0; j < pIp->pGyroData->JoinTotal; j++)
        {
            k = pIp->pGyroData->SignFlag[j];

            /*@ loop invariant 0 <= i < 3;
                loop assigns Rgtemp[j][i];
                loop variant 3 - i;
            */
            for (i = 0; i < 3; i++)
            {
                Rgtemp[j][i] = pIp->VG[k][i];
            }
        }

        /*@ loop invariant pIp->pGyroData->JoinTotal <= i <= 5;
            loop assigns Rgtemp[i][..];
            loop variant 5 - i;
        */
        for (i = pIp->pGyroData->JoinTotal; i < 5; i++)
        {
            /*@ loop invariant 0 <= j < 3;
                loop assigns Rgtemp[i][j];
                loop variant 3 - j;
            */
            for (j = 0; j < 3; j++)
            {
                Rgtemp[i][j] = 0.0f;
            }
        }

        if (pIp->pGyroData->JoinTotal >= 3)
        {
            IPCREATE(MatrixTran, ipMatrixTran, .tran = &Rgtrans[0][0], .mat = &Rgtemp[0][0], .nrow = 5, .ncol = 3);
            IPCALL(ipMatrixTran);

            IPCREATE(MatrixMulti, ipMatrixMulti_1, .product = &Rs[0][0], .faciend = &Rgtrans[0][0], .multiplier = &Rgtemp[0][0], .nrow = 3, .nrc = 5, .ncol = 3);
            IPCALL(ipMatrixMulti_1);

            unint08 MatrixInv33F_ret;
            IPCREATE(MatrixInv33F, ipMatrixInv33F, .inv = &RsInv[0][0], .src = &Rs[0][0], .ret = &(MatrixInv33F_ret));
            IPCALL(ipMatrixInv33F);

            IPCREATE(MatrixMulti, ipMatrixMulti_2, .product = &(pIp->pGyroData->Rtemp[0][0]), .faciend = &RsInv[0][0], .multiplier = &Rgtrans[0][0], .nrow = 3, .nrc = 3, .ncol = 5);
            IPCALL(ipMatrixMulti_2);
        }

        pIp->pGyroData->gyroStatus1 = pIp->pGyroData->gyroStatus0;
    }

    return;
}
