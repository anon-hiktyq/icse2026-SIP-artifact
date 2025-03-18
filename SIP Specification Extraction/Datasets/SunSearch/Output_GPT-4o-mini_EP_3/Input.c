
#include "DSSDataGet.h"
#include "JetDataGet.h"
#include "GyroStateGet.h"
#include "Input.h"

/*@ 
  requires \valid(pIp);
  assigns \nothing;
*/
void InputFun(Input *pIp)
{
    /*@ 
      requires \valid(&(pIp->mGyroData.stateFlag[0])) && \valid(&(pIp->mGyroData.wa[0]));
      assigns \nothing;
    */
    IPCREATE(GyroStateGet, ipGyroStateGet, .NumGyro = 9, .stateFlag =  &(pIp->mGyroData.stateFlag[0]), .wa =  &(pIp->mGyroData.wa[0]));
    IPCALL(ipGyroStateGet);

    /*@ 
      requires \valid(&(pIp->mDSSData));
      assigns \nothing;
    */
    IPCREATE(DSSDataGet, ipDSSDataGet, .pDSSData = &(pIp->mDSSData));
    IPCALL(ipDSSDataGet);

    /*@ 
      assigns \nothing;
    */
    IPCREATE(JetDataGet, ipJetDataGet);
    IPCALL(ipJetDataGet);

    return;
}
