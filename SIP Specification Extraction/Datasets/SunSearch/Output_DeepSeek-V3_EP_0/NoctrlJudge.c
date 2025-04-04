
#include "TripleFabsMax.h"
#include "NoctrlJudge.h"

/*@ axiomatic Sum_array {
      logic integer sum(int* array, integer begin, integer end) reads array[begin .. (end-1)];
      axiom empty:
      \forall int* a, integer b, e; b >= e ==> sum(a,b,e) == 0;
      axiom range:
      \forall int* a, integer b, e; b < e ==> sum(a,b,e) == sum(a,b,e-1) + a[e-1];
   }
*/

/*@ requires \valid(pIp);
    requires \valid(pIp->mAttitude.rate + (0..2));
    assigns pIp->mFWarning.countAV, pIp->mFWarning.Wav, pIp->nouse;
    ensures pIp->mFWarning.countAV == \old(pIp->mFWarning.countAV) + (TripleFabsMax_ret > 2.0f ? 1 : (pIp->mFWarning.countAV > 0 ? -1 : 0));
    ensures pIp->mFWarning.Wav == (pIp->mFWarning.countAV > 300 ? TRUE : \old(pIp->mFWarning.Wav));
    ensures pIp->nouse == \old(pIp->nouse);
*/
void NoctrlJudgeFun(NoctrlJudge *pIp)
{
    float32 fabsmax;
    float32 TripleFabsMax_ret;

    /*@ assert \valid(pIp->mAttitude.rate + (0..2)); */
    IPCREATE(TripleFabsMax, ipTripleFabsMax, .fx1 =  pIp->mAttitude.rate[0], .fy2 =  pIp->mAttitude.rate[1], .fz3 =  pIp->mAttitude.rate[2], .ret = &(TripleFabsMax_ret));
    IPCALL(ipTripleFabsMax);

    fabsmax = TripleFabsMax_ret;

    if (fabsmax > 2.0f)
    {
        pIp -> mFWarning.countAV++;

        if (pIp -> mFWarning.countAV > 300)
        {
            pIp -> mFWarning.Wav = TRUE;
        }
    }
    else if(pIp -> mFWarning.countAV > 0)
    {
        pIp -> mFWarning.countAV--;
    }
    else
    {
        pIp -> nouse = pIp -> nouse;
    }

    return;
}
