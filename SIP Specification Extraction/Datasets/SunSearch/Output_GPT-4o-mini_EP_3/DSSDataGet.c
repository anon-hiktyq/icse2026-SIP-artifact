
#include "Delay.h"
#include "DiviationToFloat.h"
#include "DSSDataGet.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->pDSSData);
  assigns pIp->pDSSData->stateFlag_A, pIp->pDSSData->stateFlag_B, pIp->pDSSData->flgSP, pIp->pDSSData->royaw, pIp->pDSSData->piyaw;
*/
void DSSDataGetFun(DSSDataGet *pIp)
{
    unint08 stateFlag; // Declare stateFlag outside the loop
    /*@ loop invariant 0 <= si <= 2;
        loop assigns stateFlag, pIp->pDSSData->stateFlag_A, pIp->pDSSData->stateFlag_B;
        loop variant 2 - si;
    */
    for (unint08 si = 0; si < 2; si++)
    {
        stateFlag = ADDR_READ(0xC000) & 0x3;

        if ((stateFlag & 0x1) == 0x1)
        {
            pIp->pDSSData->stateFlag_A = 1;
        }

        if ((stateFlag & 0x2) == 0x2)
        {
            pIp->pDSSData->stateFlag_B = 1;
        }
    }

    /*@ requires stateFlag > 0; 
        assigns pIp->pDSSData->royaw, pIp->pDSSData->piyaw;
    */
    if (stateFlag > 0)
    {
        ADDR_WRITE(0xA100, (0xC + si));

        IPCREATE(Delay, ipDelay, .delaytime = 500);
        IPCALL(ipDelay);

        unint08 tmp_ad_start = ADDR_READ(0xA000);

        IPCREATE(Delay, ipDelay, .delaytime = 40);
        IPCALL(ipDelay);

        unint16 tmp_lo4 = ADDR_READ(0xA003);
        unint16 tmp_hi8 = ADDR_READ(0xA001);

        unint16 wd = ((tmp_hi8 << 4) & 0x0FF0) | ((tmp_lo4 >> 4) & 0xF);
        
        /*@ loop invariant 0 <= si <= 1;
            loop assigns pIp->pDSSData->royaw, pIp->pDSSData->piyaw;
            loop variant 1 - si;
        */
        switch(si)
        {
            case 0:
            {
                /*@ logic float32 DiviationToFloat_ret; */
                IPCREATE(DiviationToFloat, ipDiviationToFloat, .input = wd, .ret = &(DiviationToFloat_ret));
                IPCALL(ipDiviationToFloat);

                pIp->pDSSData->royaw = DiviationToFloat_ret;
                break;
            }
            case 1:
            {
                /*@ logic float32 DiviationToFloat_ret; */
                IPCREATE(DiviationToFloat, ipDiviationToFloat, .input = wd, .ret = &(DiviationToFloat_ret));
                IPCALL(ipDiviationToFloat);

                pIp->pDSSData->piyaw = DiviationToFloat_ret;
                break;
            }
            default:
                break;
        }
    }

    return;
}
