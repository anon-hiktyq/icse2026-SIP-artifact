
#include "SwitchSS.h"

/*@ 
  requires \valid(pIp);
  assigns \nothing; // No memory modifications are directly observable in ACSL
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
