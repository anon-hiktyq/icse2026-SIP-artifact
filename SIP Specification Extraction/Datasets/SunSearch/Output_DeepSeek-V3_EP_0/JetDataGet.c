
#include "ThrABAutoChoose.h"
#include "JetDataGet.h"

/*@ 
  requires \valid(pIp);
  assigns pIp->mThrDistribute.stateFlag[0..1];
*/
void JetDataGetFun(JetDataGet *pIp)
{
    /*@ 
      ensures pIp->mThrDistribute.stateFlag[0] == ((ADDR_READ(0xE000) & 0x4) == 0x4 ? 1 : 0);
      assigns pIp->mThrDistribute.stateFlag[0];
    */
    if((ADDR_READ(0xE000) & 0x4) == 0x4)
    {
        pIp -> mThrDistribute.stateFlag[0] = 1;
    }
    else
    {
        pIp -> mThrDistribute.stateFlag[0] = 0;
    }

    /*@ 
      ensures pIp->mThrDistribute.stateFlag[1] == ((ADDR_READ(0xE000) & 0x8) == 0x8 ? 1 : 0);
      assigns pIp->mThrDistribute.stateFlag[1];
    */
    if((ADDR_READ(0xE000) & 0x8) == 0x8)
    {
        pIp -> mThrDistribute.stateFlag[1] = 1;
    }
    else
    {
        pIp -> mThrDistribute.stateFlag[1] = 0;
    }

    /*@ 
      assigns \nothing;
    */
    IPCREATE(ThrABAutoChoose, ipThrABAutoChoose);
    IPCALL(ipThrABAutoChoose);

    return;
}
