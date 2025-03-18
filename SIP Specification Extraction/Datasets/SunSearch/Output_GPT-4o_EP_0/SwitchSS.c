
#include "SwitchSS.h"

/*@ 
  requires \valid(pIp);
  requires \valid(&(pIp->mDSSData));
  assigns *(volatile unsigned int*)0x8000;
  ensures (pIp->mDSSData.stateFlag_A == 1) ==> (*(volatile unsigned int*)0x8000 == 0x2);
  ensures (pIp->mDSSData.stateFlag_A != 1) ==> (*(volatile unsigned int*)0x8000 == 0x1);
*/
void SwitchSSFun(SwitchSS *pIp)
{
    /*@ 
      requires \valid(pIp);
      requires \valid(&(pIp->mDSSData));
      assigns *(volatile unsigned int*)0x8000;
      ensures (pIp->mDSSData.stateFlag_A == 1) ==> (*(volatile unsigned int*)0x8000 == 0x2);
      ensures (pIp->mDSSData.stateFlag_A != 1) ==> (*(volatile unsigned int*)0x8000 == 0x1);
    */
    if (pIp->mDSSData.stateFlag_A == 1)
    {
        ADDR_WRITE(0x8000, 0x2);
    }
    else
    {
        ADDR_WRITE(0x8000, 0x1);
    }

    return;
}
