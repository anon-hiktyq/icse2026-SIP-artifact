
#include "Tr32Uint08.h"
#include "GyroProceed.h"
#include "Inputproceed.h"

/*@ 
requires \valid(pIp);
requires \valid(&(pIp->mDSSData)) && \valid(&(pIp->mAttitude)) && \valid(&(pIp->mGyroData));
assigns pIp->mAttitude.angle[0], pIp->mAttitude.angle[1];
assigns pIp->mGyroData.Gi[0], pIp->mGyroData.Gi[1];
assigns pIp->mAttitude.rate[0], pIp->mAttitude.rate[1], pIp->mAttitude.rate[2];
*/
void InputproceedFun(Inputproceed *pIp)
{
    unint08 flgSP;
    unint08 flgModetmp;
    unint08 Tr32Uint08_ret;

    IPCREATE(Tr32Uint08, ipTr32Uint08, .pA = 0, .ret = &(Tr32Uint08_ret));
    IPCALL(ipTr32Uint08);
    flgModetmp = Tr32Uint08_ret;

    IPCREATE(GyroProceed, ipGyroProceed);
    IPCALL(ipGyroProceed);

    if (flgModetmp == SAM_CRUISE)
    {
        if (pIp->mDSSData.flgSP == 1)
        {
            pIp->mAttitude.angle[0] = pIp->mDSSData.royaw;
            pIp->mAttitude.angle[1] = pIp->mDSSData.piyaw;

            pIp->mGyroData.Gi[0] = pIp->mDSSData.royaw;
            pIp->mGyroData.Gi[1] = pIp->mDSSData.piyaw;
        }
        else
        {
            pIp->mAttitude.angle[0] = pIp->mGyroData.Gi[0];
            pIp->mAttitude.angle[1] = pIp->mGyroData.Gi[1];
        }
    }
    else
    {
        pIp->mAttitude.angle[0] = 0.0f;
        pIp->mAttitude.angle[1] = 0.0f;
    }

    pIp->mAttitude.rate[0] = pIp->mGyroData.W[0];
    pIp->mAttitude.rate[1] = pIp->mGyroData.W[1];
    pIp->mAttitude.rate[2] = pIp->mGyroData.W[2];

    return;
}
