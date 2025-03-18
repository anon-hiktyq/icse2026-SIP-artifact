
#include "LimitFloat32.h"
#include "LimitCtrlAngleInput.h"

/*@ 
  requires pIp != \null; // Use \null instead of NULL
  requires \valid(pIp->pSCtrl + (0..2)); // pSCtrl has at least 3 elements
  requires \valid(pIp->pSA); // pSA is valid
  requires \valid(pIp->pSA->angle + (0..1)); // angle has at least 2 elements
  requires \valid(pIp->max); // max is valid
  assigns pIp->pSCtrl[0].Up, pIp->pSCtrl[1].Up, pIp->pSCtrl[2].Up; 
  ensures pIp->pSCtrl[0].Up == \result; // Use \result for the return value
  ensures pIp->pSCtrl[1].Up == \result; // Use \result for the return value
  ensures pIp->pSCtrl[2].Up == 0.0f; 
*/
void LimitCtrlAngleInputFun(LimitCtrlAngleInput *pIp)
{
    pIp -> pSCtrl[0].Up = pIp -> pSA->angle[0] ;
    pIp -> pSCtrl[1].Up = pIp -> pSA->angle[1] ;
    pIp -> pSCtrl[2].Up = 0.0f ;

    float32 LimitFloat32_ret_0;
    IPCREATE(LimitFloat32, ipLimitFloat32_0, .fin = pIp->pSCtrl[0].Up, .fbound =  pIp->max, .ret = &(LimitFloat32_ret_0));
    IPCALL(ipLimitFloat32_0);

    pIp -> pSCtrl[0].Up = LimitFloat32_ret_0;

    float32 LimitFloat32_ret_1;
    IPCREATE(LimitFloat32, ipLimitFloat32_1, .fin = pIp->pSCtrl[1].Up, .fbound =  pIp->max, .ret = &(LimitFloat32_ret_1));
    IPCALL(ipLimitFloat32_1);

    pIp -> pSCtrl[1].Up = LimitFloat32_ret_1;

    return;
}
