#include "GyroStateGet.h"
void GyroStateGetFun(void *p) 
{
    GyroStateGet *pIp = (GyroStateGet*)p;

	unint32 i;
	unint08 gyroRecvData[30];
	unint08 gyroSendData[2];

	gyroSendData[0] = 0xEB;
	gyroSendData[1] = 0x91;

	{IPCALL(SendUartData,ipSendUartData_0,.data = &gyroSendData[0],.len = 2,.addr = 0x881A);}					/* ��������ȡ��ָ�� */

	{IPCALL(Delay,ipDelay_0,.delaytime = 500);}									        		/* 5ms, 10us���� */

	{unint32 GetUartData_ret_0;IPCALL(GetUartData,ipGetUartData_0,.len = 30,.addr = 0x881C,.data = &gyroRecvData[0],.ret = &GetUartData_ret_0);}

	/* ��������ͨѶ���� */
	if ( (gyroRecvData[0] == 0xEB) && (gyroRecvData[1] == 0x91) )
	{
		for ( i = 0; i < pIp -> NumGyro; i++ )
		{
			/* �����������1-9 */
			pIp -> wa[i] = DIVIATION_TO_FLOAT_FOG((gyroRecvData[2 + i*2] << 8) | (gyroRecvData[2 + i*2 + 1]));

			/* ���ݼӵ�״̬1-9 */
			pIp -> stateFlag[i] = gyroRecvData[19 + i];
		}
	}

	return;
}