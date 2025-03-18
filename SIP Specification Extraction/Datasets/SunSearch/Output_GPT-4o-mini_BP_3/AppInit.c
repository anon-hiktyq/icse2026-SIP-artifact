
#include "DevControl.h"
#include "InitVar.h"
#include "AppInit.h"

/*@ requires pIp != NULL; // pIp must be a valid pointer
    assigns \nothing; // This function does not modify any global state
    ensures \result == 0; // The function does not return a value, but we can assert it completes successfully
*/
void AppInitFun(AppInit *pIp)
{
    /*@ 
        ensures ipInitVar != NULL; // ipInitVar is created successfully
        assigns \nothing; // No global variables are modified by IPCREATE
    */
    IPCREATE(InitVar, ipInitVar);
    
    /*@ 
        requires ipInitVar != NULL; // ipInitVar must be valid before calling IPCALL
        assigns \nothing; // IPCALL does not modify global state
    */
    IPCALL(ipInitVar);

    /*@ 
        ensures ipDevControl != NULL; // ipDevControl is created successfully
        assigns \nothing; // No global variables are modified by IPCREATE
    */
    IPCREATE(DevControl, ipDevControl);
    
    /*@ 
        requires ipDevControl != NULL; // ipDevControl must be valid before calling IPCALL
        assigns \nothing; // IPCALL does not modify global state
    */
    IPCALL(ipDevControl);

    /*@ 
        assigns \memory[0x8083] = 0x1; // The memory at address 0x8083 is written with the value 0x1
    */
    ADDR_WRITE(0x8083, 0x1);

    return;
}
