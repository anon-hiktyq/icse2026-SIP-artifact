
#include "SwitchSS.h"

/*@ requires pIp != \null; 
    requires pIp->mDSSData.stateFlag_A == 0 || pIp->mDSSData.stateFlag_A == 1; 
    assigns \nothing; 
    ensures \true; 
*/
void SwitchSSFun(SwitchSS *pIp)
{
    /*@ assert pIp->mDSSData.stateFlag_A == 1 || pIp->mDSSData.stateFlag_A == 0; */
    if (pIp -> mDSSData.stateFlag_A == 1)
    {
        /*@ assert \valid((void*)0x8000); */
        ADDR_WRITE(0x8000,0x2);
    }
    else
    {
        /*@ assert \valid((void*)0x8000); */
        ADDR_WRITE(0x8000,0x1);
    }

    return;
}
