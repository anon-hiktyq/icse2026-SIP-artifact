#include "Input.h"
#include "Inputproceed.h"
#include "LimitControllerInput.h"
#include "ModeControl.h"
#include "TcProcess.h"
#include "TMProcess.h"
#include "ThreeAxisController.h"
#include "FaultJudgeProceed.h"
#include "PeriodControl.h"
void PeriodControlFun(void *p)
{
    PeriodControl *pIp = (PeriodControl*)p;

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

		pIp -> flgGryoCalc = FALSE  ;

		pIp -> countSate++ ;

		if (pIp -> countSate > 0xFFFFFFF0)
		{
			pIp -> countSate = 4000 ;
		}

		    IPCREATE(TMProcess, ipTMProcess);
		    IPCALL(ipTMProcess);

		while (pIp -> flg160INT != 0xCCCC)
		{
			;
		}

		pIp -> flg160INT = 0x3333 ;

	} while(1) ;

	return;
}