
#include "MatrixInv33F.h"
#include "MatrixTran.h"
#include "MatrixMulti.h"
#include "CalculateGyroRs.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->pGyroData);
  requires \valid(pIp->pGyroData->SignFlag + (0..4));
  requires \valid(pIp->VG + (0..1) + (0..2));
  requires \valid(pIp->pGyroData->Rtemp + (0..2) + (0..4));
  ensures pIp->pGyroData->gyroStatus1 == \old(pIp->pGyroData->gyroStatus0);
  assigns pIp->flgGryoCalc, pIp->pGyroData->gyroStatus1, pIp->pGyroData->Rtemp[0..2][0..4];
*/
void CalculateGyroRsFun(CalculateGyroRs *pIp) {
    unint08 i;
    unint08 j;
    unint08 k;
    float32 Rgtrans[3][5];
    float32 Rs[3][3];
    float32 RsInv[3][3];
    float32 Rgtemp[5][3];

    pIp->pGyroData->JoinTotal = MIN(pIp->pGyroData->JoinTotal, 5);

    if (pIp->pGyroData->gyroStatus0 != pIp->pGyroData->gyroStatus1) {
        pIp->flgGryoCalc = TRUE;

        /*@ loop assigns j, i, Rgtemp[0..4][0..2];
            loop invariant 0 <= j <= pIp->pGyroData->JoinTotal;
            loop invariant \forall unint08 m; 0 <= m < j ==> 
                \forall unint08 n; 0 <= n < 3 ==> Rgtemp[m][n] == pIp->VG[pIp->pGyroData->SignFlag[m]][n];
            loop variant pIp->pGyroData->JoinTotal - j;
        */
        for (j = 0; j < pIp->pGyroData->JoinTotal; j++) {
            k = pIp->pGyroData->SignFlag[j];

            /*@ loop assigns i, Rgtemp[j][0..2];
                loop invariant 0 <= i <= 3;
                loop invariant \forall unint08 n; 0 <= n < i ==> Rgtemp[j][n] == pIp->VG[k][n];
                loop variant 3 - i;
            */
            for (i = 0; i < 3; i++) {
                Rgtemp[j][i] = pIp->VG[k][i];
            }
        }

        /*@ loop assigns i, j, Rgtemp[pIp->pGyroData->JoinTotal..4][0..2];
            loop invariant pIp->pGyroData->JoinTotal <= i <= 5;
            loop invariant \forall unint08 m; pIp->pGyroData->JoinTotal <= m < i ==> 
                \forall unint08 n; 0 <= n < 3 ==> Rgtemp[m][n] == 0.0f;
            loop variant 5 - i;
        */
        for (i = pIp->pGyroData->JoinTotal; i < 5; i++) {
            /*@ loop assigns j, Rgtemp[i][0..2];
                loop invariant 0 <= j <= 3;
                loop invariant \forall unint08 n; 0 <= n < j ==> Rgtemp[i][n] == 0.0f;
                loop variant 3 - j;
            */
            for (j = 0; j < 3; j++) {
                Rgtemp[i][j] = 0.0f;
            }
        }

        if (pIp->pGyroData->JoinTotal >= 3) {
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
