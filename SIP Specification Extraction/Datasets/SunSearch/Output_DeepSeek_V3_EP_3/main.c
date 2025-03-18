
#include "AppInit.h"
#include "PeriodControl.h"
#include "main.h"

/*@ axiomatic Sum_array {
      logic integer sum(int* array, integer begin, integer end) reads array[begin .. (end-1)];
      axiom empty:
      \forall int* a, integer b, e; b >= e ==> sum(a,b,e) == 0;
      axiom range:
      \forall int* a, integer b, e; b < e ==> sum(a,b,e) == sum(a,b,e-1) + a[e-1];
   }
*/

/*@ requires \valid(pIp) && \valid(pIp->ret);
    assigns *(pIp->ret);
    ensures *(pIp->ret) == 0;
*/
void mainFun(main *pIp)
{
    /*@ assert \valid(pIp) && \valid(pIp->ret); */

    IPCREATE(AppInit, ipAppInit);
    IPCALL(ipAppInit);

    IPCREATE(PeriodControl, ipPeriodControl);
    IPCALL(ipPeriodControl);

    /*@ assert \valid(pIp->ret); */
    *(pIp -> ret) = 0;
}
