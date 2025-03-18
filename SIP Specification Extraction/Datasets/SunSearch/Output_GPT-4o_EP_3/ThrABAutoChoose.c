
#include "ThrABAutoChoose.h"

/*@ 
requires \valid(pIp);
requires \valid(pIp -> mThrDistribute.stateFlag + (0..1));
assigns pIp -> mThrDistribute.flgABChoose;
*/
void ThrABAutoChooseFun(ThrABAutoChoose *pIp)
{
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
