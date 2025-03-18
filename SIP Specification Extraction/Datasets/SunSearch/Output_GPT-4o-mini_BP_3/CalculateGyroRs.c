
#include "MatrixInv33F.h"
#include "MatrixTran.h"
#include "MatrixMulti.h"
#include "CalculateGyroRs.h"

/*@ 
  requires pIp != \null;
  requires \valid(pIp->pGyroData);
  requires \valid(pIp->pGyroData->SignFlag + (0..pIp->pGyroData->JoinTotal-1));
  requires \valid(pIp->VG + (0..255)); // Assuming VG has at least 256 elements
  requires pIp->pGyroData->JoinTotal <= 5;
  ensures pIp->flgGryoCalc == (pIp->pGyroData->gyroStatus0 != pIp->pGyroData->gyroStatus1);
  ensures pIp->pGyroData->gyroStatus1 == pIp->pGyroData->gyroStatus0;
  ensures \forall int j; 0 <= j < pIp->pGyroData->JoinTotal ==> 
           \forall int i; 0 <= i < 3 ==> 
           \exists int k; 0 <= k < 256 ==> Rgtemp[j][i] == pIp->VG[pIp->pGyroData->SignFlag[j]][i];
  ensures \forall int i; pIp->pGyroData->JoinTotal <= i < 5 ==> 
           \forall int j; 0 <= j < 3 ==> 
           Rgtemp[i][j] == 0.0f;
  ensures \result == pIp->pGyroData->Rtemp[0][0]; // Assuming Rtemp is updated
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

		for (j = 0; j < pIp->pGyroData->JoinTotal; j++)
		{
			k = pIp->pGyroData->SignFlag[j];

			for (i = 0; i < 3; i++)
			{
				Rgtemp[j][i] = pIp->VG[k][i];
			}
		}

		for (i = pIp->pGyroData->JoinTotal; i < 5; i++)
		{
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
