
#include "SwitchSS.h"

/*@ 
  requires \valid(pIp);
  requires \valid(&(pIp->mDSSData));
  ensures \true; // Function completes without returning a value
  assigns \nothing; // No memory is modified outside of ADDR_WRITE
*/
void SwitchSSFun(SwitchSS *pIp)
{
    if (pIp -> mDSSData.stateFlag_A == 1)
    {
        ADDR_WRITE(0x8000, 0x2);
    }
    else
    {
        ADDR_WRITE(0x8000, 0x1);
    }

    return;
}
