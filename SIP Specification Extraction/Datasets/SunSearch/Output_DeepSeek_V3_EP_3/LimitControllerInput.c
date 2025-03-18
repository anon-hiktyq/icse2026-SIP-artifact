
#include "LimitCtrlRateInput.h"
#include "LimitCtrlAngleInput.h"
#include "LimitControllerInput.h"

/*@ 
  requires \valid(pIp);
  assigns pIp->mAttitude, pIp->mController[0];
*/
void LimitControllerInputFun(LimitControllerInput *pIp)
{
    /*@ 
      requires \valid(&(pIp->mAttitude)) && \valid(&(pIp->mController[0]));
      assigns pIp->mAttitude, pIp->mController[0];
    */
    IPCREATE(LimitCtrlAngleInput, ipLimitCtrlAngleInput, .pSA = &(pIp->mAttitude), .pSCtrl =  &(pIp->mController[0]), .max =  0.8f);
    IPCALL(ipLimitCtrlAngleInput);

    /*@ 
      requires \valid(&(pIp->mAttitude)) && \valid(&(pIp->mController[0]));
      assigns pIp->mAttitude, pIp->mController[0];
    */
    IPCREATE(LimitCtrlRateInput, ipLimitCtrlRateInput, .pSA = &(pIp->mAttitude), .pSCtrl =  &(pIp->mController[0]), .max =  1.2f);
    IPCALL(ipLimitCtrlRateInput);

    return ;
}
