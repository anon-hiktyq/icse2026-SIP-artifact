
#include "AppInit.h"
#include "PeriodControl.h"
#include "main.h"

/*@ 
requires \valid(pIp);
requires \valid(pIp->ret);
ensures *(pIp->ret) == 0;
assigns *(pIp->ret);
*/
void mainFun(main *pIp)
{
    /*@ assert \valid(pIp); */
    /*@ assert \valid(pIp->ret); */

    IPCREATE(AppInit, ipAppInit);
    IPCALL(ipAppInit);

    IPCREATE(PeriodControl, ipPeriodControl);
    IPCALL(ipPeriodControl);

    /*@ assert \valid(pIp->ret); */
    *(pIp->ret) = 0;
}
