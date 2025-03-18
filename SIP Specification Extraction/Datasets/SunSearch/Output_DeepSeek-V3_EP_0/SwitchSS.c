
#include "SwitchSS.h"

/*@ 
  requires \valid(pIp);
  assigns \nothing;
  ensures \result == \null;
*/
void SwitchSSFun(SwitchSS *pIp)
{
    /*@ 
      requires \valid(&pIp->mDSSData.stateFlag_A);
      assigns \nothing;
    */
    if (pIp->mDSSData.stateFlag_A == 1)
    {
        /*@ 
          assigns \nothing;
        */
        ADDR_WRITE(0x8000, 0x2);
    }
    else
    {
        /*@ 
          assigns \nothing;
        */
        ADDR_WRITE(0x8000, 0x1);
    }

    return;
}
