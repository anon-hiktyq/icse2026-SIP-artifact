#include "Input.h"
void InputFun(void *p) 
{
    Input *pIp = (Input*)p;

	/* �������ݲɼ� */
	{IPCALL(GyroStateGet,ipGyroStateGet_0,.NumGyro = 9,.stateFlag = &mGyroData.stateFlag[0],.wa = &mGyroData.wa[0]);}

	/* ̫�����ݲɼ� */
	{IPCALL(DSSDataGet,ipDSSDataGet_0,.pDSSData = &mDSSData);}

	/* ���������ݲɼ� */
	{IPCALL(JetDataGet,ipJetDataGet_0);}

    return;
}