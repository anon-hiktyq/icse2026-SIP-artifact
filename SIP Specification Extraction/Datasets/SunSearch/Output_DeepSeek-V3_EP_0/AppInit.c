
#include "DevControl.h"
#include "InitVar.h"
#include "AppInit.h"

/*@ 
  requires \valid(pIp);
  assigns \nothing;
*/
void AppInitFun(AppInit *pIp)
{
    IPCREATE(InitVar, ipInitVar);
    IPCALL(ipInitVar);

    IPCREATE(DevControl, ipDevControl);
    IPCALL(ipDevControl);

    /*@ 
      assigns \nothing;
    */
    ADDR_WRITE(0x8083, 0x1);

    return;
}
