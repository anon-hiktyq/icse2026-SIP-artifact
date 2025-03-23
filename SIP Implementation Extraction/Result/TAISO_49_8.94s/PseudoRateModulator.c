#include "PseudoRateModulator.h"
void PseudoRateModulatorFun(void *p) 
{
    PseudoRateModulator *pIp = (PseudoRateModulator*)p;

	if ((pIp -> pModulator->u - pIp -> pModulator->r) > pIp -> h1)					/* u(����)-r�������źţ�>pIp -> h1 */
	{
		pIp -> pModulator->Yp = 0x0 ;									/* ����32ms������ */
		pIp -> pModulator->Yn = 0xF ;
		pIp -> pModulator->r = 0.9231f * pIp -> pModulator->r + 0.07688f ;	/*  Y=1 */
	}
	else if ((pIp -> pModulator->u - pIp -> pModulator->r) < -pIp -> h1)				/* u(����)-r�������źţ�<pIp -> h1 */
	{
		pIp -> pModulator->Yp = 0xF ;									/* ����32ms������ */
		pIp -> pModulator->Yn = 0x0 ;
		pIp -> pModulator->r = 0.9231f * pIp -> pModulator->r - 0.07688f ;	/* Y=-1  */
	}
	else														/* ���� */
	{
		pIp -> pModulator->Yp = 0x0 ;									/* ���� */
		pIp -> pModulator->Yn = 0x0 ;
		pIp -> pModulator->r = 0.9231f * pIp -> pModulator->r ;				/* Y=0  */
	}

	return ;
}