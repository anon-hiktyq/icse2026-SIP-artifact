#include "SendUartData.h"
void SendUartDataFun(void *p)
{
    SendUartData *pIp = (SendUartData*)p;

	unint32 i;
	for (i = 0; i < pIp -> len; i++)
	{
		ADDR_WRITE(pIp -> addr, pIp -> data[i]);
	}
	return;
}