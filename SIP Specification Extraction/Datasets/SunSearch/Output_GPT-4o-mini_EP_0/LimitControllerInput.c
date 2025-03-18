
#include "LimitCtrlRateInput.h"
#include "LimitCtrlAngleInput.h"
#include "LimitControllerInput.h"

/*@ 
  requires \valid(pIp);
  requires \valid(&(pIp->mAttitude));
  requires \valid(&(pIp->mController[0]));
  assigns \nothing;
*/
void LimitControllerInputFun(LimitControllerInput *pIp)
{
    /*@ 
      ensures \result == \old(\result); 
    */
	IPCREATE(LimitCtrlAngleInput, ipLimitCtrlAngleInput, .pSA = &(pIp->mAttitude), .pSCtrl =  &(pIp->mController[0]), .max =  0.8f);
	IPCALL(ipLimitCtrlAngleInput);

    /*@ 
      ensures \result == \old(\result); 
    */
    IPCREATE(LimitCtrlRateInput, ipLimitCtrlRateInput, .pSA = &(pIp->mAttitude), .pSCtrl =  &(pIp->mController[0]), .max =  1.2f);
    IPCALL(ipLimitCtrlRateInput);

    return;
}
