
#include "AppInit.h"
#include "PeriodControl.h"
#include "main.h"

/*@ requires pIp != NULL; 
    requires \valid(pIp->ret); 
    assigns *(pIp->ret); 
    ensures *(pIp->ret) == 0; */
void mainFun(main *pIp)
{
    /*@ ghost AppInit ipAppInit; */
    IPCREATE(AppInit, ipAppInit);
    IPCALL(ipAppInit);

    /*@ ghost PeriodControl ipPeriodControl; */
    IPCREATE(PeriodControl, ipPeriodControl);
    IPCALL(ipPeriodControl);

    *(pIp -> ret) = 0;
}
