#include "GetUartData.h"
void GetUartDataFun(void *p) 
{
    GetUartData *pIp = (GetUartData*)p;

	unint32 fifoCnt;
	unint32 i;
	unint32 pIp -> bSucc;

	pIp -> bSucc = 0;
	fifoCnt = ADDR_READ(0x88D0);   /* ��ȡ���ڽ��ճ��ȼ��� */		/* QUERY(ZM) �����ַ��������? */

	if (fifoCnt == pIp -> len)
	{
		for (i = 0; i < pIp -> len; i++)
		{
			pIp -> data[i] = ADDR_READ(pIp -> addr);
		}

		pIp -> bSucc = 1;	
	}

	*(pIp -> ret) = bSucc;
}