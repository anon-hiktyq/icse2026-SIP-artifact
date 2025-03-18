#include "GetUartData.h"
void GetUartDataFun(GetUartData *pIp)
{

	unint32 fifoCnt;
	unint32 i;
	

	pIp -> bSucc = 0;
	fifoCnt = ADDR_READ(0x88D0);

	if (fifoCnt == pIp -> len)
	{
		for (i = 0; i < pIp -> len; i++)
		{
			pIp -> data[i] = ADDR_READ(pIp -> addr);
		}

		pIp -> bSucc = 1;
	}

	*(pIp -> ret) = pIp -> bSucc;
}