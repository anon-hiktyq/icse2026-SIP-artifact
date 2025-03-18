
#include "ModeControl.h"
#include "Input.h"
#include "ThreeAxisController.h"
#include "Inputproceed.h"
#include "LimitControllerInput.h"
#include "TMProcess.h"
#include "FaultJudgeProceed.h"
#include "TcProcess.h"
#include "PeriodControl.h"

/*@ requires pIp != \null;
    @ ensures \true; // The function runs indefinitely, so no specific postcondition can be guaranteed.
    @ assigns pIp->flgGryoCalc, pIp->countSate, pIp->flg160INT; // The function modifies these fields of the PeriodControl structure.
    @ loop invariant pIp->countSate >= 0; // countSate should always be non-negative.
    @ loop invariant pIp->countSate <= 0xFFFFFFF0; // countSate should not exceed the upper limit before reset.
    @ loop invariant pIp->flg160INT == 0x3333 || pIp->flg160INT == 0xCCCC; // flg160INT should be one of these two values during the loop.
    @ loop variant 1; // The loop is infinite, but we can note that the loop variant is always positive.
*/
void PeriodControlFun(PeriodControl *pIp)
{
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

        while (pIp->flg160INT != 0xCCCC)
        {
            ;
        }

        pIp->flg160INT = 0x3333;

    } while(1);

    return;
}
