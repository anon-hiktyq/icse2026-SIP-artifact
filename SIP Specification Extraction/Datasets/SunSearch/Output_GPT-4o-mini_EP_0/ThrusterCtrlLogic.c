
#include "ThrusterCtrlLogic.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->mModulator + (0..2)); // Assuming mModulator has at least 3 elements
  assigns pIp->mThrDistribute.wPulse;
*/
void ThrusterCtrlLogicFun(ThrusterCtrlLogic *pIp)
{
    /*@ loop invariant \valid(pIp);
        loop assigns pIp->mThrDistribute.wPulse;
    */
    if ( pIp -> mModulator[0].Yp != 0)
    {
        pIp -> mThrDistribute.wPulse = pIp -> mThrDistribute.wPulse | 0x04 ;
    }

    if ( pIp -> mModulator[0].Yn != 0)
    {
        pIp -> mThrDistribute.wPulse = pIp -> mThrDistribute.wPulse | 0x08 ;
    }

    if ( pIp -> mModulator[1].Yp != 0)
    {
        pIp -> mThrDistribute.wPulse = pIp -> mThrDistribute.wPulse | 0x10 ;
    }

    if ( pIp -> mModulator[1].Yn != 0)
    {
        pIp -> mThrDistribute.wPulse = pIp -> mThrDistribute.wPulse | 0x20 ;
    }

    if ( pIp -> mModulator[2].Yp != 0)
    {
        pIp -> mThrDistribute.wPulse = pIp -> mThrDistribute.wPulse | 0x40 ;
    }

    if ( pIp -> mModulator[2].Yn != 0)
    {
        pIp -> mThrDistribute.wPulse = pIp -> mThrDistribute.wPulse | 0x80 ;
    }

    return;
}
