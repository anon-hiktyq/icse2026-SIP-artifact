
#include "B_TcProcess.h"
#include "GetUartData.h"
#include "TcProcess.h"

/*@ requires pIp != NULL; // pIp must be a valid pointer
    requires \valid(pIp); // pIp must be a valid pointer
    assigns GetUartData_ret; // GetUartData_ret is assigned a value
    ensures GetUartData_ret == 1 ==> \valid(tcaData + (0..3)); // If GetUartData_ret is 1, tcaData must be valid for the first 4 elements
    ensures GetUartData_ret == 1 ==> \valid(pIp->tcaData); // If GetUartData_ret is 1, pIp->tcaData must be valid
*/
void TcProcessFun(TcProcess *pIp)
{
    /*@ ghost unint08 tcaData[32]; // Declare tcaData as a ghost variable for ACSL purposes */
    unint08 tcaData[32];

    unint32 GetUartData_ret;
    IPCREATE(GetUartData, ipGetUartData, .len = 4, .addr =  0x88DA, .data =  &tcaData[0], .ret = &(GetUartData_ret));
    IPCALL(ipGetUartData);

    /*@ assert GetUartData_ret == 1 ==> \valid(tcaData + (0..3)); // Assert that if GetUartData_ret is 1, the first 4 elements of tcaData are valid */
    if (GetUartData_ret == 1)
    {
        IPCREATE(B_TcProcess, ipB_TcProcess, .tcaData = &tcaData[0]);
        IPCALL(ipB_TcProcess);
    }

    return;
}
