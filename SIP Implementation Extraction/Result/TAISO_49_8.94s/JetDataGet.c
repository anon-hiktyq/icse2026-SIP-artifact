#include "JetDataGet.h"
void JetDataGetFun(void *p) 
{
    JetDataGet *pIp = (JetDataGet*)p;

	if((ADDR_READ(0xE000) & 0x4) == 0x4)
	{
		pIp -> mThrDistribute.stateFlag[0] = 1;
	}
	else
	{
		pIp -> mThrDistribute.stateFlag[0] = 0;
	}


	if((ADDR_READ(0xE000) & 0x8) == 0x8)
	{
		pIp -> mThrDistribute.stateFlag[1] = 1;
	}
	else
	{
		pIp -> mThrDistribute.stateFlag[1] = 0;
	}

	{IPCALL(ThrABAutoChoose,ipThrABAutoChoose_0);}										/* ��LV14BASA��LV23BASB���ñ�־ */

	return;
}