#include "TcProcess.h"
void TcProcessFun(void *p) 
{
    TcProcess *pIp = (TcProcess*)p;
    
    unint08 tcaData[32];
    unint32 t;{unint32 GetUartData_ret_1;IPCALL(GetUartData,ipGetUartData_1,.len = 4,.addr = 0x88DA,.data = &tcaData[0],.ret = &GetUartData_ret_1);t = GetUartData_ret_1}  //test添加语句

    {unint32 GetUartData_ret_0;IPCALL(GetUartData,ipGetUartData_0,.len = 4,.addr = 0x88DA,.data = &tcaData[0],.ret = &GetUartData_ret_0);if ((GetUartData_ret_0)== 1) 
	{
		/* ��������ָ������ */		
		{IPCALL(B_TcProcess,ipB_TcProcess_0,.tcaData = &tcaData[0]);}          /* ָ��� */		
	}}
   	
    return;
}