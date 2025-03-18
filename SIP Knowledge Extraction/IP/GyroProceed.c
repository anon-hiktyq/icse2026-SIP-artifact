#include "ModPNHP.h"
#include "CalculateGyroDg.h"
#include "GyroChoose.h"
#include "GyroPick.h"
#include "CalculateGyroRs.h"
#include "GyroProceed.h"
void GyroProceedFun(void *p)
{
    GyroProceed *pIp = (GyroProceed*)p;

    float32 dgi[2] ;

    IPCREATE(GyroPick, ipGyroPick, .pGyroData = &(pIp->mGyroData));
    IPCALL(ipGyroPick);

    IPCREATE(GyroChoose, ipGyroChoose, .pGyroData = &(pIp->mGyroData));
    IPCALL(ipGyroChoose);

	IPCREATE(CalculateGyroRs, ipCalculateGyroRs, .pGyroData = &(pIp->mGyroData));
	IPCALL(ipCalculateGyroRs);

    IPCREATE(CalculateGyroDg, ipCalculateGyroDg, .pGyroData = &(pIp->mGyroData));
    IPCALL(ipCalculateGyroDg);

    dgi[0] = pIp -> mGyroData.Gi[0] + pIp -> mGyroData.W[0] * 0.160f ;
    dgi[1] = pIp -> mGyroData.Gi[1] + pIp -> mGyroData.W[1] * 0.160f ;

    float32 ModPNHP_ret;
    IPCREATE(ModPNHP, ipModPNHP, .x = dgi[0], .halfperiod =  180.0f, .ret = &(ModPNHP_ret));
    IPCALL(ipModPNHP);

    pIp -> mGyroData.Gi[0] = ModPNHP_ret;

    float32 ModPNHP_ret;
    IPCREATE(ModPNHP, ipModPNHP, .x = dgi[1], .halfperiod =  180.0f, .ret = &(ModPNHP_ret));
    IPCALL(ipModPNHP);

    pIp -> mGyroData.Gi[1] = ModPNHP_ret;

    return ;
}