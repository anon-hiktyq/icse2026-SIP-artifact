#include "DSSDataGet.h"
#include "JetDataGet.h"
#include "GyroStateGet.h"
#include "Input.h"

/*@ 
requires \valid(pIp);
requires \valid(&(pIp->mGyroData.stateFlag[0])) && \valid(&(pIp->mGyroData.wa[0]));
requires \valid(&(pIp->mDSSData));
assigns *(&(pIp->mGyroData.stateFlag[0])), *(&(pIp->mGyroData.wa[0])), *(&(pIp->mDSSData));
ensures \true;
*/
void InputFun(Input *pIp)
{
    /*@ 
    requires \valid(&(pIp->mGyroData.stateFlag[0])) && \valid(&(pIp->mGyroData.wa[0]));
    assigns *(&(pIp->mGyroData.stateFlag[0])), *(&(pIp->mGyroData.wa[0]));
    ensures \true;
    */
    IPCREATE(GyroStateGet, ipGyroStateGet, .NumGyro = 9, .stateFlag =  &(pIp->mGyroData.stateFlag[0]), .wa =  &(pIp->mGyroData.wa[0]));
    IPCALL(ipGyroStateGet);

    /*@ 
    requires \valid(&(pIp->mDSSData));
    assigns *(&(pIp->mDSSData));
    ensures \true;
    */
    IPCREATE(DSSDataGet, ipDSSDataGet, .pDSSData = &(pIp->mDSSData));
    IPCALL(ipDSSDataGet);

    /*@ 
    ensures \true;
    */
    IPCREATE(JetDataGet, ipJetDataGet);
    IPCALL(ipJetDataGet);

    return;
}
