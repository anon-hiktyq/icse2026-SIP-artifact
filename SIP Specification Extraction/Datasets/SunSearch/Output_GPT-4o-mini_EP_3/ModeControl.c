
#include "SAMSubModePitch.h"
#include "SAMSubModeCruise.h"
#include "SAMSubModeDamp.h"
#include "SAMSubModeRoll.h"
#include "Tr32Uint08.h"
#include "ModeControl.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->mController);
  requires \valid(pIp->mDSSData);
  requires \valid(pIp->mAttitude.rate);
  ensures \result == \old(pIp->countMode) + 1;
  assigns pIp->countMode;
*/
void ModeControlFun(ModeControl *pIp)
{
    unint32 flgModetmp1;

    unint08 Tr32Uint08_ret;
    IPCREATE(Tr32Uint08, ipTr32Uint08, .pA = 0 , .ret = &(Tr32Uint08_ret));
    IPCALL(ipTr32Uint08);

    flgModetmp1 = Tr32Uint08_ret;

    pIp->countMode++;

    /* Loop construct for handling mode changes */
    /*@ loop invariant flgModetmp1 == SAM_DAMP || flgModetmp1 == SAM_PITCH || flgModetmp1 == SAM_ROLL || flgModetmp1 == SAM_CRUISE;
        loop assigns pIp->countMode;
    */
    switch (flgModetmp1) {
        case SAM_DAMP:
            IPCREATE(SAMSubModeDamp, ipSAMSubModeDamp, .rate = &(pIp->mAttitude.rate[0]), .max =  0.15f, .countPublic = pIp->countPublic, .countMode = pIp->countMode, .flgMode =  SAM_DAMP);
            IPCALL(ipSAMSubModeDamp);
            break;
        case SAM_PITCH:
            IPCREATE(SAMSubModePitch, ipSAMSubModePitch, .pSDS = &(pIp->mDSSData), .countPublic = pIp->countPublic, .countMode = pIp->countMode, .flgMode =  SAM_PITCH, .pCtrl =  &(pIp->mController[0]));
            IPCALL(ipSAMSubModePitch);
            break;
        case SAM_ROLL:
            IPCREATE(SAMSubModeRoll, ipSAMSubModeRoll, .pSDS = &(pIp->mDSSData), .countPublic = pIp->countPublic, .countMode = pIp->countMode, .flgMode =  SAM_ROLL, .pCtrl =  &(pIp->mController[0]));
            IPCALL(ipSAMSubModeRoll);
            break;
        case SAM_CRUISE:
            IPCREATE(SAMSubModeCruise, ipSAMSubModeCruise, .countMode = pIp->countMode, .Count160ms = pIp->Count160ms, .mFWarning = pIp->mFWarning);
            IPCALL(ipSAMSubModeCruise);
            break;
        default:
            TR32_FLGMODE_VALUE(SAM_DAMP);
            break;
    }

    return;
}
