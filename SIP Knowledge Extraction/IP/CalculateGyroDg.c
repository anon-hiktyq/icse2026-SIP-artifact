#include "MatrixMulti.h"
#include "CalculateGyroDg.h"
#include "MatrixMulti.h"
void CalculateGyroDgFun(void *p)
{
    CalculateGyroDg *pIp = (CalculateGyroDg*)p;

 	unint08 j ;
	unint08 k ;
	float32 tmpwa[5] ;

	for (j = 0 ; j < 5 ; j++ )
	{
	     tmpwa[j] = 0 ;
    }
	for ( j=0 ; j < pIp -> pGyroData->JoinTotal ; j++ )
	{
		k = pIp -> pGyroData->SignFlag[j] ;
		tmpwa[j] = pIp -> pGyroData->wa[k] ;
	}

	if ( pIp -> pGyroData->JoinTotal >= 3 )
	{

		IPCREATE(MatrixMulti, ipMatrixMulti, .product = &(pIp->pGyroData->W[0]), .faciend =  &(pIp->pGyroData->Rtemp[0][0]), .multiplier =  &tmpwa[0], .nrow =  3, .nrc =  5, .ncol =  1);
		IPCALL(ipMatrixMulti);
	
	}
	else
	{
		pIp -> pGyroData->W[0] = 0.0f ;
		pIp -> pGyroData->W[1] = 0.0f ;
		pIp -> pGyroData->W[2] = 0.0f ;
	}

	return ;
}