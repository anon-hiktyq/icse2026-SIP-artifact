#include "B_TcProcess.h"
#include "GetUartData.h"
#include "TcProcess.h"
void TcProcessFun(TcProcess *pIp)
{

    unint08 tcaData[32];

    unint32 GetUartData_ret;
    IPCREATE(GetUartData, ipGetUartData, .len = 4, .addr =  0x88DA, .data =  &tcaData[0], .ret = &(GetUartData_ret));
    IPCALL(ipGetUartData);

    if (GetUartData_ret== 1)
	{

		IPCREATE(B_TcProcess, ipB_TcProcess, .tcaData = &tcaData[0]);
		IPCALL(ipB_TcProcess);

	}

    return;
}