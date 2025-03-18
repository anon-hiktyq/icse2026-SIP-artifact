#include "SwitchSS.h"
void SwitchSSFun(SwitchSS *pIp)
{

    if (pIp -> mDSSData.stateFlag_A == 1)
    {

		ADDR_WRITE(0x8000,0x2);
    }
    else
    {

		ADDR_WRITE(0x8000,0x1);
    }

    return ;
}