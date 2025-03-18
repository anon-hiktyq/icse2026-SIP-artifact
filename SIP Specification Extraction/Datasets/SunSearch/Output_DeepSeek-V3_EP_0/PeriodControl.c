
#include "ModeControl.h"
#include "Input.h"
#include "ThreeAxisController.h"
#include "Inputproceed.h"
#include "LimitControllerInput.h"
#include "TMProcess.h"
#include "FaultJudgeProceed.h"
#include "TcProcess.h"
#include "PeriodControl.h"

/*@ axiomatic StateCounter {
      logic integer state_counter(PeriodControl *pIp) = pIp->countSate;
      axiom state_counter_reset:
        \forall PeriodControl *pIp; state_counter(pIp) > 0xFFFFFFF0 ==> state_counter(pIp) == 4000;
   }
*/

/*@ requires \valid(pIp);
    assigns pIp->countSate, pIp->flgGryoCalc, pIp->flg160INT;
    ensures pIp->countSate == \old(pIp->countSate) + 1 || pIp->countSate == 4000;
    ensures pIp->flg160INT == 0x3333;
*/
void PeriodControlFun(PeriodControl *pIp)
{
    /*@ loop invariant pIp->countSate >= 0;
        loop assigns pIp->countSate, pIp->flgGryoCalc, pIp->flg160INT;
        loop variant 0xFFFFFFF0 - pIp->countSate;
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

        /*@ loop invariant pIp->flg160INT == 0xCCCC;
            loop assigns pIp->flg160INT;
            loop variant 0xCCCC - pIp->flg160INT;
        */
        while (pIp->flg160INT != 0xCCCC)
        {
            ;
        }

        pIp->flg160INT = 0x3333;

    } while(1);

    return;
}
