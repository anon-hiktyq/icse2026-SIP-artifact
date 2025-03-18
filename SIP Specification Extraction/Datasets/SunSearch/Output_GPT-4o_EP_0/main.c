
#include "AppInit.h"
#include "PeriodControl.h"
#include "main.h"

/*@ 
requires \valid(pIp) && \valid(pIp->ret);
assigns *(pIp->ret);
ensures *(pIp->ret) == 0;
*/
void mainFun(main *pIp)
{
    IPCREATE(AppInit, ipAppInit);
    IPCALL(ipAppInit);

    IPCREATE(PeriodControl, ipPeriodControl);
    IPCALL(ipPeriodControl);

    *(pIp -> ret) = 0;
}
