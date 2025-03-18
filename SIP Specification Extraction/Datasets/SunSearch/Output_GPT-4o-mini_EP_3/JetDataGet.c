
#include "ThrABAutoChoose.h"
#include "JetDataGet.h"

/*@ 
  requires \valid(pIp);
  ensures pIp->mThrDistribute.stateFlag[0] == 1 ==> (ADDR_READ(0xE000) & 0x4) == 0x4;
  ensures pIp->mThrDistribute.stateFlag[0] == 0 ==> (ADDR_READ(0xE000) & 0x4) != 0x4;
  ensures pIp->mThrDistribute.stateFlag[1] == 1 ==> (ADDR_READ(0xE000) & 0x8) == 0x8;
  ensures pIp->mThrDistribute.stateFlag[1] == 0 ==> (ADDR_READ(0xE000) & 0x8) != 0x8;
  assigns pIp->mThrDistribute.stateFlag[0], pIp->mThrDistribute.stateFlag[1];
*/
void JetDataGetFun(JetDataGet *pIp)
{
    /*@
      requires \valid(pIp);
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
      requires \valid(pIp);
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

    IPCREATE(ThrABAutoChoose, ipThrABAutoChoose);
    IPCALL(ipThrABAutoChoose);

    return;
}
