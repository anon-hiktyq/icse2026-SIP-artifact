
#include "LimitCtrlRateInput.h"
#include "LimitCtrlAngleInput.h"
#include "LimitControllerInput.h"

/*@ requires pIp != NULL;
    requires \valid(pIp);
    requires \valid(pIp->mAttitude);
    requires \valid(pIp->mController + (0..N-1)); // Assuming N is the size of mController array
    assigns \nothing;
    ensures \result == \nothing; // The function does not return a value
*/
void LimitControllerInputFun(LimitControllerInput *pIp)
{
    /*@ 
        creates ipLimitCtrlAngleInput; 
        requires \valid(pIp);
        assigns \nothing; // No state is modified here
        ensures \valid(ipLimitCtrlAngleInput); // Ensure the created object is valid
        ensures ipLimitCtrlAngleInput.pSA == &(pIp->mAttitude);
        ensures ipLimitCtrlAngleInput.pSCtrl == &(pIp->mController[0]);
        ensures ipLimitCtrlAngleInput.max == 0.8f;
    */
    LimitCtrlAngleInput ipLimitCtrlAngleInput; // Declare the variable
	IPCREATE(LimitCtrlAngleInput, ipLimitCtrlAngleInput, .pSA = &(pIp->mAttitude), .pSCtrl =  &(pIp->mController[0]), .max =  0.8f);
	IPCALL(ipLimitCtrlAngleInput);

    /*@ 
        creates ipLimitCtrlRateInput; 
        requires \valid(pIp);
        assigns \nothing; // No state is modified here
        ensures \valid(ipLimitCtrlRateInput); // Ensure the created object is valid
        ensures ipLimitCtrlRateInput.pSA == &(pIp->mAttitude);
        ensures ipLimitCtrlRateInput.pSCtrl == &(pIp->mController[0]);
        ensures ipLimitCtrlRateInput.max == 1.2f;
    */
    LimitCtrlRateInput ipLimitCtrlRateInput; // Declare the variable
    IPCREATE(LimitCtrlRateInput, ipLimitCtrlRateInput, .pSA = &(pIp->mAttitude), .pSCtrl =  &(pIp->mController[0]), .max =  1.2f);
    IPCALL(ipLimitCtrlRateInput);

    return ;
}
