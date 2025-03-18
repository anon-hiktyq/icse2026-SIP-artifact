
#include "DSSDataGet.h"
#include "JetDataGet.h"
#include "GyroStateGet.h"
#include "Input.h"

/*@
  requires \valid(pIp);
  requires \valid(pIp->mGyroData.stateFlag + (0..8));
  requires \valid(pIp->mGyroData.wa + (0..8));
  requires \valid(&pIp->mDSSData);
  assigns pIp->mGyroData.stateFlag[0..8], pIp->mGyroData.wa[0..8], pIp->mDSSData;
*/
void InputFun(Input *pIp)
{
    /*@ assert \valid(pIp->mGyroData.stateFlag + (0..8)) && \valid(pIp->mGyroData.wa + (0..8)); */
    IPCREATE(GyroStateGet, ipGyroStateGet, .NumGyro = 9, .stateFlag =  &(pIp->mGyroData.stateFlag[0]), .wa =  &(pIp->mGyroData.wa[0]));
    IPCALL(ipGyroStateGet);

    /*@ assert \valid(&pIp->mDSSData); */
    IPCREATE(DSSDataGet, ipDSSDataGet, .pDSSData = &(pIp->mDSSData));
    IPCALL(ipDSSDataGet);

    IPCREATE(JetDataGet, ipJetDataGet);
    IPCALL(ipJetDataGet);

    return;
}
