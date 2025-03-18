
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
    assigns \nothing;
    */
    IPCREATE(InitVar, ipInitVar);
    
    /*@ 
    assigns \nothing;
    */
    IPCALL(ipInitVar);

    /*@ 
    assigns \nothing;
    */
    IPCREATE(DevControl, ipDevControl);
    
    /*@ 
    assigns \nothing;
    */
    IPCALL(ipDevControl);

    /*@ 
    assigns *((volatile unsigned int *)0x8083);
    ensures *((volatile unsigned int *)0x8083) == 0x1;
    */
    ADDR_WRITE(0x8083, 0x1);

    return;
}
