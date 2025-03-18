
#include "MatrixInv33F.h"
#include "MatrixTran.h"
#include "MatrixMulti.h"
#include "CalculateGyroRs.h"

/*@ axiomatic MatrixOperations {
      logic real sum(real* array, integer begin, integer end) reads array[begin .. (end-1)];
      axiom empty:
        \forall real* a, integer b, e; b >= e ==> sum(a,b,e) == 0.0;
      axiom range:
        \forall real* a, integer b, e; b < e ==> sum(a,b,e) == sum(a,b,e-1) + a[e-1];
    }
*/

/*@ requires \valid(pIp);
    requires \valid(pIp->pGyroData);
    requires \valid(pIp->pGyroData->SignFlag + (0..4));
    requires \valid(pIp->VG + (0..2));
    requires \valid(pIp->pGyroData->Rtemp + (0..2));
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

    /*@ assigns pIp->pGyroData->JoinTotal;
        ensures pIp->pGyroData->JoinTotal == \min(\old(pIp->pGyroData->JoinTotal), 5);
    */
    pIp->pGyroData->JoinTotal = MIN(pIp->pGyroData->JoinTotal, 5);

    if (pIp->pGyroData->gyroStatus0 != pIp->pGyroData->gyroStatus1) {
        /*@ assigns pIp->flgGryoCalc;
            ensures pIp->flgGryoCalc == TRUE;
        */
        pIp->flgGryoCalc = TRUE;

        /*@ loop invariant 0 <= j <= pIp->pGyroData->JoinTotal;
            loop assigns j, k, Rgtemp[0..4][0..2];
            loop variant pIp->pGyroData->JoinTotal - j;
        */
        for (j = 0; j < pIp->pGyroData->JoinTotal; j++) {
            k = pIp->pGyroData->SignFlag[j];

            /*@ loop invariant 0 <= i <= 3;
                loop assigns i, Rgtemp[j][0..2];
                loop variant 3 - i;
            */
            for (i = 0; i < 3; i++) {
                Rgtemp[j][i] = pIp->VG[k][i];
            }
        }

        /*@ loop invariant pIp->pGyroData->JoinTotal <= i <= 5;
            loop assigns i, j, Rgtemp[0..4][0..2];
            loop variant 5 - i;
        */
        for (i = pIp->pGyroData->JoinTotal; i < 5; i++) {
            /*@ loop invariant 0 <= j <= 3;
                loop assigns j, Rgtemp[i][0..2];
                loop variant 3 - j;
            */
            for (j = 0; j < 3; j++) {
                Rgtemp[i][j] = 0.0f;
            }
        }

        if (pIp->pGyroData->JoinTotal >= 3) {
            /*@ requires \valid(&Rgtrans[0][0]) && \valid(&Rgtemp[0][0]);
                assigns Rgtrans[0..2][0..4];
            */
            IPCREATE(MatrixTran, ipMatrixTran, .tran = &Rgtrans[0][0], .mat = &Rgtemp[0][0], .nrow = 5, .ncol = 3);
            IPCALL(ipMatrixTran);

            /*@ requires \valid(&Rs[0][0]) && \valid(&Rgtrans[0][0]) && \valid(&Rgtemp[0][0]);
                assigns Rs[0..2][0..2];
            */
            IPCREATE(MatrixMulti, ipMatrixMulti_1, .product = &Rs[0][0], .faciend = &Rgtrans[0][0], .multiplier = &Rgtemp[0][0], .nrow = 3, .nrc = 5, .ncol = 3);
            IPCALL(ipMatrixMulti_1);

            unint08 MatrixInv33F_ret;
            /*@ requires \valid(&RsInv[0][0]) && \valid(&Rs[0][0]);
                assigns RsInv[0..2][0..2], MatrixInv33F_ret;
            */
            IPCREATE(MatrixInv33F, ipMatrixInv33F, .inv = &RsInv[0][0], .src = &Rs[0][0], .ret = &(MatrixInv33F_ret));
            IPCALL(ipMatrixInv33F);

            /*@ requires \valid(&(pIp->pGyroData->Rtemp[0][0])) && \valid(&RsInv[0][0]) && \valid(&Rgtrans[0][0]);
                assigns pIp->pGyroData->Rtemp[0..2][0..4];
            */
            IPCREATE(MatrixMulti, ipMatrixMulti_2, .product = &(pIp->pGyroData->Rtemp[0][0]), .faciend = &RsInv[0][0], .multiplier = &Rgtrans[0][0], .nrow = 3, .nrc = 3, .ncol = 5);
            IPCALL(ipMatrixMulti_2);
        }

        /*@ assigns pIp->pGyroData->gyroStatus1;
            ensures pIp->pGyroData->gyroStatus1 == \old(pIp->pGyroData->gyroStatus0);
        */
        pIp->pGyroData->gyroStatus1 = pIp->pGyroData->gyroStatus0;
    }

    return;
}
