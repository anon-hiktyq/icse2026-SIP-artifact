
#include "ThrABAutoChoose.h"

/*@
  requires \valid(pIp);
  requires \valid(&pIp->mThrDistribute.stateFlag[0]) && \valid(&pIp->mThrDistribute.stateFlag[1]);
  requires \valid(&pIp->mThrDistribute.flgABChoose);
  assigns pIp->mThrDistribute.flgABChoose;
  ensures (pIp->mThrDistribute.stateFlag[0] == 1 && pIp->mThrDistribute.stateFlag[1] == 1) ==> 
            pIp->mThrDistribute.flgABChoose == TBS_AB;
  ensures (pIp->mThrDistribute.stateFlag[0] == 0 && pIp->mThrDistribute.stateFlag[1] == 1) ==> 
            pIp->mThrDistribute.flgABChoose == TBS_B;
  ensures (pIp->mThrDistribute.stateFlag[0] != 1 || pIp->mThrDistribute.stateFlag[1] != 1) && 
            (pIp->mThrDistribute.stateFlag[0] != 0 || pIp->mThrDistribute.stateFlag[1] != 1) ==> 
            pIp->mThrDistribute.flgABChoose == TBS_A;
*/
void ThrABAutoChooseFun(ThrABAutoChoose *pIp)
{
    if ((pIp->mThrDistribute.stateFlag[0] = 1) &&
        (pIp->mThrDistribute.stateFlag[1] = 1))
    {
        pIp->mThrDistribute.flgABChoose = TBS_AB;
    }
    else if ((pIp->mThrDistribute.stateFlag[0] = 0) &&
             (pIp->mThrDistribute.stateFlag[1] = 1))
    {
        pIp->mThrDistribute.flgABChoose = TBS_B;
    }
    else
    {
        pIp->mThrDistribute.flgABChoose = TBS_A;
    }

    return;
}
