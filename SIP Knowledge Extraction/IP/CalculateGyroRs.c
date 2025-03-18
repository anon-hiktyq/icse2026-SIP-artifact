#include "MatrixTran.h"
#include "MatrixMulti.h"
#include "MatrixInv33F.h"
#include "CalculateGyroRs.h"
void CalculateGyroRsFun(void *p)
{
    CalculateGyroRs *pIp = (CalculateGyroRs*)p;

	unint08 i ;
 	unint08 j ;
	unint08 k ;
 	float32 Rgtrans[3][5] ;
 	float32 Rs[3][3] ;
	float32 RsInv[3][3] ;
 	float32 Rgtemp[5][3] ;

 	pIp -> pGyroData->JoinTotal = MIN(pIp -> pGyroData->JoinTotal, 5) ;

	if (pIp -> pGyroData->gyroStatus0 != pIp -> pGyroData->gyroStatus1)
	{
		pIp -> flgGryoCalc = TRUE ;

		for ( j = 0 ; j < pIp -> pGyroData->JoinTotal ; j++ )
		{
			k = pIp -> pGyroData->SignFlag[j] ;

			for ( i=0 ;  i<3 ; i++ )
			{
				Rgtemp[j][i] = pIp -> VG[k][i] ;
			}
		}

		for ( i = pIp -> pGyroData->JoinTotal ; i<5 ; i++ )
		{
			for ( j=0 ; j<3 ; j++ )
			{
				Rgtemp[i][j] = 0.0f;
			}
		}

		if (pIp -> pGyroData->JoinTotal >= 3)
		{

			IPCREATE(MatrixTran, ipMatrixTran, .tran = &Rgtrans[0][0], .mat =  &Rgtemp[0][0], .nrow =  5, .ncol =  3);
			IPCALL(ipMatrixTran);

			IPCREATE(MatrixMulti, ipMatrixMulti, .product = &Rs[0][0], .faciend =  &Rgtrans[0][0], .multiplier =  &Rgtemp[0][0], .nrow =  3, .nrc =  5, .ncol =  3);
			IPCALL(ipMatrixMulti);

			unint08 MatrixInv33F_ret;
			IPCREATE(MatrixInv33F, ipMatrixInv33F, .inv = &RsInv[0][0], .src =  &Rs[0][0], .ret = &(MatrixInv33F_ret));
			IPCALL(ipMatrixInv33F);

			MatrixInv33F_ret;

			IPCREATE(MatrixMulti, ipMatrixMulti, .product = &(pIp->pGyroData->Rtemp[0][0]), .faciend =  &RsInv[0][0], .multiplier =  &Rgtrans[0][0], .nrow =  3, .nrc =  3, .ncol =  5);
			IPCALL(ipMatrixMulti);

		}

		pIp -> pGyroData->gyroStatus1 = pIp -> pGyroData->gyroStatus0 ;
	}

	return ;
}