
#include "Delay.h"
#include "DiviationToFloat.h"
#include "SendUartData.h"
#include "GetUartData.h"
#include "GyroStateGet.h"

/*@ 
  requires \valid(pIp);
  requires \valid(gyroRecvData + (0..29));
  requires \valid(gyroSendData + (0..1));
  assigns pIp->wa[0..pIp->NumGyro-1], pIp->stateFlag[0..pIp->NumGyro-1];
*/
void GyroStateGetFun(GyroStateGet *pIp)
{
    /*@ loop invariant 0 <= i <= pIp->NumGyro;
        loop variant pIp->NumGyro - i;
    */
    for (unint32 i = 0; i < pIp->NumGyro; i++)
    {
        /*@ 
          requires \valid(pIp);
          requires \valid(gyroRecvData + (0..29));
          requires \valid(pIp->wa + (0..pIp->NumGyro-1));
          requires \valid(pIp->stateFlag + (0..pIp->NumGyro-1));
          ensures pIp->wa[i] == DiviationToFloat_ret;
          ensures pIp->stateFlag[i] == gyroRecvData[19 + i];
          assigns pIp->wa[i], pIp->stateFlag[i];
        */
        float32 DiviationToFloat_ret;
        IPCREATE(DiviationToFloat, ipDiviationToFloat, .input = (gyroRecvData[2 + i * 2] << 8) | (gyroRecvData[2 + i * 2 + 1]), .ret = &(DiviationToFloat_ret));
        IPCALL(ipDiviationToFloat);

        pIp->wa[i] = DiviationToFloat_ret;
        pIp->stateFlag[i] = gyroRecvData[19 + i];
    }

    return;
}
