#include "AppInit.h"
#include "PeriodControl.h"
#include "main.h"
void mainFun(void *p)
{
    main *pIp = (main*)p;

	IPCREATE(AppInit, ipAppInit);
	IPCALL(ipAppInit);

	IPCREATE(PeriodControl, ipPeriodControl);
	IPCALL(ipPeriodControl);

    *(pIp -> ret) = 0;
}