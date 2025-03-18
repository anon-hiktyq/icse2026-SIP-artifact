#include "GetUartData.h"
#include "DiviationToFloat.h"
#include "SendUartData.h"
#include "Delay.h"
#include "GyroStateGet.h"
void GyroStateGetFun(void *p)
{
    GyroStateGet *pIp = (GyroStateGet*)p;

	unint32 i;
	unint08 gyroRecvData[30];
	unint08 gyroSendData[2];

	gyroSendData[0] = 0xEB;
	gyroSendData[1] = 0x91;

	IPCREATE(SendUartData, ipSendUartData, .data = &gyroSendData[0], .len =  2, .addr =  0x881A);
	IPCALL(ipSendUartData);

	IPCREATE(Delay, ipDelay, .delaytime = 500);
	IPCALL(ipDelay);

	unint32 GetUartData_ret;
	IPCREATE(GetUartData, ipGetUartData, .len = 30, .addr =  0x881C, .data =  &gyroRecvData[0], .ret = &(GetUartData_ret));
	IPCALL(ipGetUartData);

	if ( (gyroRecvData[0] == 0xEB) && (gyroRecvData[1] == 0x91) )
	{
		for ( i = 0; i < pIp -> NumGyro; i++ )
		{

			float32 DiviationToFloat_ret;
			IPCREATE(DiviationToFloat, ipDiviationToFloat, .input = (gyroRecvData[2 + i*2] << 8) | (gyroRecvData[2 + i*2 + 1]), .ret = &(DiviationToFloat_ret));
			IPCALL(ipDiviationToFloat);

			pIp -> wa[i] = DiviationToFloat_ret;

			pIp -> stateFlag[i] = gyroRecvData[19 + i];
		}
	}

	return;
}