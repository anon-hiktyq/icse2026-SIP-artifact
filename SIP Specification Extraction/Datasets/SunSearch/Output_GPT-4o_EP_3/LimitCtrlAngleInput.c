
#include "LimitFloat32.h"
#include "LimitCtrlAngleInput.h"

/*@ 
requires \valid(pIp);
requires \valid(pIp->pSCtrl + (0..2));
requires \valid(pIp->pSA);
requires \valid(pIp->pSA->angle + (0..1));
requires \valid(&(pIp->pSCtrl[0].Up));
requires \valid(&(pIp->pSCtrl[1].Up));
requires \valid(&(pIp->pSCtrl[2].Up));
requires \valid(&(pIp->max));
ensures \valid(&(pIp->pSCtrl[0].Up));
ensures \valid(&(pIp->pSCtrl[1].Up));
ensures \valid(&(pIp->pSCtrl[2].Up));
assigns pIp->pSCtrl[0].Up, pIp->pSCtrl[1].Up, pIp->pSCtrl[2].Up;
*/
void LimitCtrlAngleInputFun(LimitCtrlAngleInput *pIp)
{
    pIp->pSCtrl[0].Up = pIp->pSA->angle[0];
    pIp->pSCtrl[1].Up = pIp->pSA->angle[1];
    pIp->pSCtrl[2].Up = 0.0f;

    float32 LimitFloat32_ret_0;
    IPCREATE(LimitFloat32, ipLimitFloat32_0, .fin = pIp->pSCtrl[0].Up, .fbound = pIp->max, .ret = &(LimitFloat32_ret_0));
    IPCALL(ipLimitFloat32_0);

    pIp->pSCtrl[0].Up = LimitFloat32_ret_0;

    float32 LimitFloat32_ret_1;
    IPCREATE(LimitFloat32, ipLimitFloat32_1, .fin = pIp->pSCtrl[1].Up, .fbound = pIp->max, .ret = &(LimitFloat32_ret_1));
    IPCALL(ipLimitFloat32_1);

    pIp->pSCtrl[1].Up = LimitFloat32_ret_1;

    return;
}
