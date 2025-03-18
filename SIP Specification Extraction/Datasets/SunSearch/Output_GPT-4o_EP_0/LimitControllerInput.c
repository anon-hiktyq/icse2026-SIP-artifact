
#include "LimitCtrlRateInput.h"
#include "LimitCtrlAngleInput.h"
#include "LimitControllerInput.h"

/*@ requires \valid(pIp);
    requires \valid(&(pIp->mAttitude));
    requires \valid(&(pIp->mController[0]));
    assigns *(pIp->mController), pIp->mAttitude;
    ensures \true; // Placeholder, as the function does not return a value or modify the input in a way that needs postconditions
*/
void LimitControllerInputFun(LimitControllerInput *pIp)
{
    /*@ requires \valid(&(pIp->mAttitude));
        requires \valid(&(pIp->mController[0]));
        assigns *(pIp->mController), pIp->mAttitude;
        ensures \true; // Placeholder, as the function does not return a value or modify the input in a way that needs postconditions
    */
	IPCREATE(LimitCtrlAngleInput, ipLimitCtrlAngleInput, .pSA = &(pIp->mAttitude), .pSCtrl =  &(pIp->mController[0]), .max =  0.8f);
	IPCALL(ipLimitCtrlAngleInput);

    /*@ requires \valid(&(pIp->mAttitude));
        requires \valid(&(pIp->mController[0]));
        assigns *(pIp->mController), pIp->mAttitude;
        ensures \true; // Placeholder, as the function does not return a value or modify the input in a way that needs postconditions
    */
    IPCREATE(LimitCtrlRateInput, ipLimitCtrlRateInput, .pSA = &(pIp->mAttitude), .pSCtrl =  &(pIp->mController[0]), .max =  1.2f);
    IPCALL(ipLimitCtrlRateInput);

    return ;
}
