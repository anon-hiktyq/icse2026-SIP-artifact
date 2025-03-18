
#include "SwitchSS.h"

/*@ 
  requires \valid(pIp);
  requires \valid(&pIp->mDSSData);
  ensures \result == 0; // No return value, but ensures function completes
  assigns \nothing; // No state is modified outside of ADDR_WRITE
*/
void SwitchSSFun(SwitchSS *pIp)
{
    /*@ 
      loop invariant pIp != NULL;
      loop variant 1; // No loop, but we can use a variant for clarity
    */
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
