#include "AppInit.h"
#include "PeriodControl.h"
#include "main.h"
void mainFun(main *pIp)
{

	IPCREATE(AppInit, ipAppInit);
	IPCALL(ipAppInit);

	IPCREATE(PeriodControl, ipPeriodControl);
	IPCALL(ipPeriodControl);

    *(pIp -> ret) = 0;
}