
#include "B_TcProcess.h"
#include "GetUartData.h"
#include "TcProcess.h"

/*@ 
  requires \valid(pIp);
  assigns \nothing;
*/
void TcProcessFun(TcProcess *pIp)
{
    /*@ 
      requires \valid(tcaData + (0..31));
      assigns tcaData[0..31], GetUartData_ret;
      ensures \result == \old(GetUartData_ret);
    */
    unint08 tcaData[32];

    unint32 GetUartData_ret;
    
    IPCREATE(GetUartData, ipGetUartData, .len = 4, .addr =  0x88DA, .data =  &tcaData[0], .ret = &(GetUartData_ret));
    IPCALL(ipGetUartData);

    /*@ 
      requires GetUartData_ret == 1;
      assigns \nothing;
    */
    if (GetUartData_ret == 1)
    {
        IPCREATE(B_TcProcess, ipB_TcProcess, .tcaData = &tcaData[0]);
        IPCALL(ipB_TcProcess);
    }

    return;
}
