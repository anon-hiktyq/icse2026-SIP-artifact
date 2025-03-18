#include "ModPNHP.h"
void ModPNHPFun(ModPNHP *pIp)
{

    float32 period;


    period = 2.0f * pIp -> halfperiod;

    pIp -> npp2 = pIp -> x - (pIp -> x + pIp -> halfperiod) / period * period;

    *(pIp -> ret) = pIp -> npp2;
    }