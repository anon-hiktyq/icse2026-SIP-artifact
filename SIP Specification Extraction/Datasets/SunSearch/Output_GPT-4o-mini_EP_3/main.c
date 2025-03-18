
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
      assigns ipAppInit; // No need for requires since ipAppInit is not a pointer
    */
    IPCREATE(AppInit, ipAppInit);
    IPCALL(ipAppInit);

    /*@ 
      assigns ipPeriodControl; // No need for requires since ipPeriodControl is not a pointer
    */
    IPCREATE(PeriodControl, ipPeriodControl);
    IPCALL(ipPeriodControl);

    *(pIp->ret) = 0;
}
