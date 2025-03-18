
#include "B_TcProcess.h"
#include "GetUartData.h"
#include "TcProcess.h"

/*@ 
  requires \valid(pIp);
  assigns tcaData[0..31], GetUartData_ret;
  ensures \result == \old(GetUartData_ret);
*/
void TcProcessFun(TcProcess *pIp)
{
    unint08 tcaData[32];

    unint32 GetUartData_ret;

    /*@ 
      requires \valid(&tcaData[0]) && \valid(&GetUartData_ret);
      assigns tcaData[0..3], GetUartData_ret;
    */
    IPCREATE(GetUartData, ipGetUartData, .len = 4, .addr =  0x88DA, .data =  &tcaData[0], .ret = &(GetUartData_ret));
    IPCALL(ipGetUartData);

    if (GetUartData_ret == 1)
    {
        /*@ 
          requires \valid(&tcaData[0]);
          assigns \nothing;
        */
        IPCREATE(B_TcProcess, ipB_TcProcess, .tcaData = &tcaData[0]);
        IPCALL(ipB_TcProcess);
    }

    return;
}
