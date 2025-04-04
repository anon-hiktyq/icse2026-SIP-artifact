
#include "DevControl.h"
#include "InitVar.h"
#include "AppInit.h"

/*@ 
  requires \valid(pIp);
  assigns \nothing; 
*/
void AppInitFun(AppInit *pIp)
{
    /*@ 
      requires \valid(pIp); // Validate the pointer to AppInit
      assigns \nothing; 
    */
    IPCREATE(InitVar, ipInitVar);
    IPCALL(ipInitVar);

    /*@ 
      requires \valid(pIp); // Validate the pointer to AppInit
      assigns \nothing; 
    */
    IPCREATE(DevControl, ipDevControl);
    IPCALL(ipDevControl);

    /*@ 
      assigns *(volatile int*)0x8083; 
    */
    ADDR_WRITE(0x8083, 0x1);

    return;
}
