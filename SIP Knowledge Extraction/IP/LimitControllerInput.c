#include "LimitCtrlAngleInput.h"
#include "LimitCtrlRateInput.h"
#include "LimitControllerInput.h"
void LimitControllerInputFun(void *p)
{
    LimitControllerInput *pIp = (LimitControllerInput*)p;

	IPCREATE(LimitCtrlAngleInput, ipLimitCtrlAngleInput, .pSA = &(pIp->mAttitude), .pSCtrl =  &(pIp->mController[0]), .max =  0.8f);
	IPCALL(ipLimitCtrlAngleInput);

    IPCREATE(LimitCtrlRateInput, ipLimitCtrlRateInput, .pSA = &(pIp->mAttitude), .pSCtrl =  &(pIp->mController[0]), .max =  1.2f);
    IPCALL(ipLimitCtrlRateInput);

    return ;
}