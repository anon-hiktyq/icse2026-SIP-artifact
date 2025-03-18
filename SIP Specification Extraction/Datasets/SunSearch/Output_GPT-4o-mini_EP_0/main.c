
#include "AppInit.h"
#include "PeriodControl.h"
#include "main.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->ret);
  assigns *(pIp->ret);
*/
void mainFun(main *pIp)
{
    /*@ 
      requires \valid(ipAppInit);
      assigns ipAppInit;
    */
    IPCREATE(AppInit, ipAppInit);
    IPCALL(ipAppInit);

    /*@ 
      requires \valid(ipPeriodControl);
      assigns ipPeriodControl;
    */
    IPCREATE(PeriodControl, ipPeriodControl);
    IPCALL(ipPeriodControl);

    *(pIp -> ret) = 0;
}
