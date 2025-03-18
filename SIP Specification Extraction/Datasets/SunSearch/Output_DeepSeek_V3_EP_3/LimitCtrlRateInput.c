
#include "LimitFloat32.h"
#include "Tr32Float.h"
#include "LimitCtrlRateInput.h"

/*@ axiomatic Sum_array {
      logic integer sum(int* array, integer begin, integer end) reads array[begin .. (end-1)];
      axiom empty:
      \forall int* a, integer b, e; b >= e ==> sum(a,b,e) == 0;
      axiom range:
      \forall int* a, integer b, e; b < e ==> sum(a,b,e) == sum(a,b,e-1) + a[e-1];
   }
*/

/*@ requires \valid(pIp);
    requires \valid(pIp->pSA);
    requires \valid(pIp->pSCtrl + (0..2));
    requires \valid(pIp->pSA->rate + (0..2));
    assigns pIp->pSCtrl[0..2].Ud;
*/
void LimitCtrlRateInputFun(LimitCtrlRateInput *pIp)
{
    float32 Tr32Float_ret;
    IPCREATE(Tr32Float, ipTr32Float, .pA = 0, .ret = &(Tr32Float_ret));
    IPCALL(ipTr32Float);

    /*@ assigns pIp->pSCtrl[0].Ud, pIp->pSCtrl[1].Ud, pIp->pSCtrl[2].Ud; */
    pIp->pSCtrl[0].Ud = pIp->pSA->rate[0] - Tr32Float_ret;
    pIp->pSCtrl[1].Ud = pIp->pSA->rate[1] - Tr32Float_ret;
    pIp->pSCtrl[2].Ud = pIp->pSA->rate[2];

    float32 LimitFloat32_ret_0;
    IPCREATE(LimitFloat32, ipLimitFloat32_0, .fin = pIp->pSCtrl[0].Ud, .fbound = pIp->max, .ret = &(LimitFloat32_ret_0));
    IPCALL(ipLimitFloat32_0);

    /*@ assigns pIp->pSCtrl[0].Ud; */
    pIp->pSCtrl[0].Ud = LimitFloat32_ret_0;

    float32 LimitFloat32_ret_1;
    IPCREATE(LimitFloat32, ipLimitFloat32_1, .fin = pIp->pSCtrl[1].Ud, .fbound = pIp->max, .ret = &(LimitFloat32_ret_1));
    IPCALL(ipLimitFloat32_1);

    /*@ assigns pIp->pSCtrl[1].Ud; */
    pIp->pSCtrl[1].Ud = LimitFloat32_ret_1;

    float32 LimitFloat32_ret_2;
    IPCREATE(LimitFloat32, ipLimitFloat32_2, .fin = pIp->pSCtrl[2].Ud, .fbound = pIp->max, .ret = &(LimitFloat32_ret_2));
    IPCALL(ipLimitFloat32_2);

    /*@ assigns pIp->pSCtrl[2].Ud; */
    pIp->pSCtrl[2].Ud = LimitFloat32_ret_2;

    return;
}
