
#include "ThrusterCtrlLogic.h"

/*@
  requires \valid(pIp);
  requires \valid(pIp->mModulator + (0..2));
  requires \valid(&pIp->mThrDistribute);
  assigns pIp->mThrDistribute.wPulse;
*/
void ThrusterCtrlLogicFun(ThrusterCtrlLogic *pIp)
{
    /*@
      loop invariant 0 <= i <= 3;
      loop assigns pIp->mThrDistribute.wPulse;
      loop variant 3 - i;
    */
    for (int i = 0; i < 3; i++) {
        if (pIp->mModulator[i].Yp != 0) {
            pIp->mThrDistribute.wPulse |= (0x04 << (2 * i));
        }
        if (pIp->mModulator[i].Yn != 0) {
            pIp->mThrDistribute.wPulse |= (0x08 << (2 * i));
        }
    }

    return;
}
