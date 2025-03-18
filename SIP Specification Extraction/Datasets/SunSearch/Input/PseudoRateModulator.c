#include "PseudoRateModulator.h"
void PseudoRateModulatorFun(PseudoRateModulator *pIp)
{

	if ((pIp -> pModulator->u - pIp -> pModulator->r) > pIp -> h1)
	{
		pIp -> pModulator->Yp = 0x0 ;
		pIp -> pModulator->Yn = 0xF ;
		pIp -> pModulator->r = 0.9231f * pIp -> pModulator->r + 0.07688f ;
	}
	else if ((pIp -> pModulator->u - pIp -> pModulator->r) < -pIp -> h1)
	{
		pIp -> pModulator->Yp = 0xF ;
		pIp -> pModulator->Yn = 0x0 ;
		pIp -> pModulator->r = 0.9231f * pIp -> pModulator->r - 0.07688f ;
	}
	else
	{
		pIp -> pModulator->Yp = 0x0 ;
		pIp -> pModulator->Yn = 0x0 ;
		pIp -> pModulator->r = 0.9231f * pIp -> pModulator->r ;
	}

	return ;
}