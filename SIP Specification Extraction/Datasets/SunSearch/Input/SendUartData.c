#include "SendUartData.h"
void SendUartDataFun(SendUartData *pIp)
{

	unint32 i;
	for (i = 0; i < pIp -> len; i++)
	{
		ADDR_WRITE(pIp -> addr, pIp -> data[i]);
	}
	return;
}