#include "GyroChoose.h"
void GyroChooseFun(void *p)
{
    GyroChoose *pIp = (GyroChoose*)p;

	unint08 i ;

	pIp -> pGyroData->JoinTotal = 0 ;
	pIp -> pGyroData->gyroStatus0 = 0 ;

	for ( i=0 ; i<9 ; i++ )
	{
		if (pIp -> pGyroData->stateFlag[i] == TRUE)
		{
			pIp -> pGyroData->SignFlag[pIp -> pGyroData->JoinTotal] = i ;
			pIp -> pGyroData->JoinTotal++ ;
			pIp -> pGyroData->gyroStatus0 = pIp -> pGyroData->gyroStatus0 | (1 << i) ;
		}

	}

	return ;
}