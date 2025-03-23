#include "ThrABAutoChoose.h"
void ThrABAutoChooseFun(void *p) 
{
    ThrABAutoChoose *pIp = (ThrABAutoChoose*)p;

    if ((pIp -> mThrDistribute.stateFlag[0] = 1) &&
        (pIp -> mThrDistribute.stateFlag[1] = 1))
    {
        /* AB��֧���ӵ�,����Ϊ˫��֧ */
        pIp -> mThrDistribute.flgABChoose = TBS_AB ;
    }
    else if ((pIp -> mThrDistribute.stateFlag[0] = 0) &&
             (pIp -> mThrDistribute.stateFlag[1] = 1))
    {
        pIp -> mThrDistribute.flgABChoose = TBS_B ;
    }
    else
    {
        pIp -> mThrDistribute.flgABChoose = TBS_A ;
    }

    return ;
}