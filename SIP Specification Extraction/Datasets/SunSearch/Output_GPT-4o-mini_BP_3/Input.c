
#include "DSSDataGet.h"
#include "JetDataGet.h"
#include "GyroStateGet.h"
#include "Input.h"

/*@ 
  @ requires pIp != \null; 
  @ ensures \valid(pIp);
  @ ensures \valid(pIp->mGyroData.stateFlag + (0..8));
  @ ensures \valid(pIp->mGyroData.wa + (0..8));
  @ ensures \valid(pIp->mDSSData);
  @ assigns pIp->mGyroData.stateFlag[0..8], pIp->mGyroData.wa[0..8], pIp->mDSSData;
*/
void InputFun(Input *pIp)
{
    int i; // Declare loop variable

    /*@
      @ loop invariant 0 <= i <= 9;
      @ loop assigns pIp->mGyroData.stateFlag[i], pIp->mGyroData.wa[i];
      @ loop variant 9 - i;
    */
    for (i = 0; i < 9; i++) {
        // Loop body can be empty as IPCREATE is not inside the loop
    }

    IPCREATE(GyroStateGet, ipGyroStateGet, .NumGyro = 9, .stateFlag =  &(pIp->mGyroData.stateFlag[0]), .wa =  &(pIp->mGyroData.wa[0]));
    IPCALL(ipGyroStateGet);

    IPCREATE(DSSDataGet, ipDSSDataGet, .pDSSData = &(pIp->mDSSData));
    IPCALL(ipDSSDataGet);

    IPCREATE(JetDataGet, ipJetDataGet);
    IPCALL(ipJetDataGet);

    return;
}
