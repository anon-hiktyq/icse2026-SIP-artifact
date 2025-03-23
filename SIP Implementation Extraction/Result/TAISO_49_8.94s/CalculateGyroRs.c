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

	if (pIp -> pGyroData->gyroStatus0 != pIp -> pGyroData->gyroStatus1)		/* �������л� */
	{
		pIp -> flgGryoCalc = TRUE ;								/* �����ݼ����־ */

		for ( j = 0 ; j < pIp -> pGyroData->JoinTotal ; j++ )			/* �μӶ��˵����ݸ��� */
		{
			k = pIp -> pGyroData->SignFlag[j] ;						/* ����С������������ѡ5��������5��ѡ���µ� */

			for ( i=0 ;  i<3 ; i++ )
			{
				Rgtemp[j][i] = pIp -> VG[k][i] ;					/* n*3�İ�װ��R */
			}
		}

		for ( i = pIp -> pGyroData->JoinTotal ; i<5 ; i++ )			/* ���õģ�5-JoinTotal��ά������ */
		{
			for ( j=0 ; j<3 ; j++ )
			{
				Rgtemp[i][j] = 0.0f;
			}
		}

		if (pIp -> pGyroData->JoinTotal >= 3)						/* �������������ݹ������Լ�����ٶ� */
		{

			{IPCALL(MatrixTran,ipMatrixTran_0,.tran = &Rgtrans[0][0],.mat = &Rgtemp[0][0],.nrow = 5,.ncol = 3);};					/* Rg->Rgtrans    		*/
			{IPCALL(MatrixMulti,ipMatrixMulti_1,.product = &Rs[0][0],.faciend = &Rgtrans[0][0],.multiplier = &Rgtemp[0][0],.nrow = 3,.nrc = 5,.ncol = 3);};	/* R*RT->RS       		*/
			{unint08 MatrixInv33F_ret_0;IPCALL(MatrixInv33F,ipMatrixInv33F_0,.inv = &RsInv[0][0],.src = &Rs[0][0],.ret = &MatrixInv33F_ret_0);};								/* INV(RS)->RsInv 		*/
			{IPCALL(MatrixMulti,ipMatrixMulti_0,.product = &(pIp->pGyroData->Rtemp[0][0]),.faciend = &RsInv[0][0],.multiplier = &Rgtrans[0][0],.nrow = 3,.nrc = 3,.ncol = 5);};	/* RsInv*Rgtrans->Rtemp */
		}

		pIp -> pGyroData->gyroStatus1 = pIp -> pGyroData->gyroStatus0 ;
	}

	return ;
}