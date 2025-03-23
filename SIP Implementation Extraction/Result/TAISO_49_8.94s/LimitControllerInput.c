#include "LimitControllerInput.h"
void LimitControllerInputFun(void *p) 
{
    LimitControllerInput *pIp = (LimitControllerInput*)p;

	{IPCALL(LimitCtrlAngleInput,ipLimitCtrlAngleInput_0,.pSA = &mAttitude,.pSCtrl = &mController[0],.max = 0.8f);}		/* �Ƕ��޷� */

    {IPCALL(LimitCtrlRateInput,ipLimitCtrlRateInput_0,.pSA = &mAttitude,.pSCtrl = &mController[0],.max = 1.2f);}			/* ���ٶ��޷� */

    return ;
}