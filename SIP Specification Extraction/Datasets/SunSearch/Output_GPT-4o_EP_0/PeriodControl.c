
#include "ModeControl.h"
#include "Input.h"
#include "ThreeAxisController.h"
#include "Inputproceed.h"
#include "LimitControllerInput.h"
#include "TMProcess.h"
#include "FaultJudgeProceed.h"
#include "TcProcess.h"
#include "PeriodControl.h"

/*@ 
requires \valid(pIp);
assigns pIp->flgGryoCalc, pIp->countSate, pIp->flg160INT;
*/
void PeriodControlFun(PeriodControl *pIp)
{
    /*@ loop invariant \valid(pIp);
        loop assigns pIp->flgGryoCalc, pIp->countSate, pIp->flg160INT;
        loop variant 0; // Infinite loop, variant is constant
    */
    do
    {
        IPCREATE(TcProcess, ipTcProcess);
        IPCALL(ipTcProcess);

        IPCREATE(Input, ipInput);
        IPCALL(ipInput);

        IPCREATE(Inputproceed, ipInputproceed);
        IPCALL(ipInputproceed);

        IPCREATE(ModeControl, ipModeControl);
        IPCALL(ipModeControl);

        IPCREATE(LimitControllerInput, ipLimitControllerInput);
        IPCALL(ipLimitControllerInput);

        IPCREATE(ThreeAxisController, ipThreeAxisController);
        IPCALL(ipThreeAxisController);

        IPCREATE(FaultJudgeProceed, ipFaultJudgeProceed);
        IPCALL(ipFaultJudgeProceed);

        pIp->flgGryoCalc = FALSE;

        pIp->countSate++;

        if (pIp->countSate > 0xFFFFFFF0)
        {
            pIp->countSate = 4000;
        }

        IPCREATE(TMProcess, ipTMProcess);
        IPCALL(ipTMProcess);

        /*@ loop invariant \valid(pIp);
            loop assigns pIp->flg160INT;
            loop variant 0; // Infinite loop, variant is constant
        */
        while (pIp->flg160INT != 0xCCCC)
        {
            ;
        }

        pIp->flg160INT = 0x3333;

    } while(1);

    return;
}
