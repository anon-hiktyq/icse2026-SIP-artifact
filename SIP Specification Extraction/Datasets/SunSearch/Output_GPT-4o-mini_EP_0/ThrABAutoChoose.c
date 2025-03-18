
#include "ThrABAutoChoose.h"

/*@ 
  requires \valid(pIp);
  ensures \valid(pIp->mThrDistribute.stateFlag);
  assigns pIp->mThrDistribute.flgABChoose;
*/
void ThrABAutoChooseFun(ThrABAutoChoose *pIp)
{
    /*@ loop invariant \valid(pIp);
        loop assigns pIp->mThrDistribute.flgABChoose;
    */
    if ((pIp -> mThrDistribute.stateFlag[0] == 1) &&
        (pIp -> mThrDistribute.stateFlag[1] == 1))
    {
        pIp -> mThrDistribute.flgABChoose = TBS_AB;
    }
    else if ((pIp -> mThrDistribute.stateFlag[0] == 0) &&
             (pIp -> mThrDistribute.stateFlag[1] == 1))
    {
        pIp -> mThrDistribute.flgABChoose = TBS_B;
    }
    else
    {
        pIp -> mThrDistribute.flgABChoose = TBS_A;
    }

    return;
}
