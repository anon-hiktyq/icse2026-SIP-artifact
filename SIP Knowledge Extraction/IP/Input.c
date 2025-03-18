#include "DSSDataGet.h"
#include "GyroStateGet.h"
#include "JetDataGet.h"
#include "Input.h"
void InputFun(void *p)
{
    Input *pIp = (Input*)p;

	IPCREATE(GyroStateGet, ipGyroStateGet, .NumGyro = 9, .stateFlag =  &(pIp->mGyroData.stateFlag[0]), .wa =  &(pIp->mGyroData.wa[0]));
	IPCALL(ipGyroStateGet);

	IPCREATE(DSSDataGet, ipDSSDataGet, .pDSSData = &(pIp->mDSSData));
	IPCALL(ipDSSDataGet);

	IPCREATE(JetDataGet, ipJetDataGet);
	IPCALL(ipJetDataGet);

    return;
}