
#include "LimitCtrlRateInput.h"
#include "LimitCtrlAngleInput.h"
#include "LimitControllerInput.h"

/*@ 
  requires \valid(pIp) && \valid(&(pIp->mAttitude)) && \valid(&(pIp->mController[0]));
  assigns pIp->mController[0], pIp->mAttitude;
  ensures \true; // Placeholder for actual postconditions
*/
void LimitControllerInputFun(LimitControllerInput *pIp)
{
    IPCREATE(LimitCtrlAngleInput, ipLimitCtrlAngleInput, .pSA = &(pIp->mAttitude), .pSCtrl =  &(pIp->mController[0]), .max =  0.8f);
    IPCALL(ipLimitCtrlAngleInput);

    IPCREATE(LimitCtrlRateInput, ipLimitCtrlRateInput, .pSA = &(pIp->mAttitude), .pSCtrl =  &(pIp->mController[0]), .max =  1.2f);
    IPCALL(ipLimitCtrlRateInput);

    return;
}
