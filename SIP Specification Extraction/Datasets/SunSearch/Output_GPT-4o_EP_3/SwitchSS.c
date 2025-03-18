
#include "SwitchSS.h"

/*@ 
requires \valid(pIp);
requires \valid(&(pIp->mDSSData));
ensures (pIp->mDSSData.stateFlag_A == 1) ==> \true;
ensures (pIp->mDSSData.stateFlag_A != 1) ==> \true;
assigns \nothing;
*/
void SwitchSSFun(SwitchSS *pIp)
{
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
