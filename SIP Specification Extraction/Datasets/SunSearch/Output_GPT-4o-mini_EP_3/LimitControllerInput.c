
#include "LimitCtrlRateInput.h"
#include "LimitCtrlAngleInput.h"
#include "LimitControllerInput.h"

/*@ 
  requires \valid(pIp); 
  requires \valid(&(pIp->mAttitude)); 
  requires \valid(pIp->mController + (0..N-1)); // N should be defined as a parameter
  requires N > 0; // Ensuring N is a positive integer
  assigns \nothing; 
*/
void LimitControllerInputFun(LimitControllerInput *pIp, int N) // Changed integer to int
{
    /*@ 
      ensures \valid(&(pIp->mAttitude)); 
      ensures \valid(&(pIp->mController[0])); 
    */
	IPCREATE(LimitCtrlAngleInput, ipLimitCtrlAngleInput, .pSA = &(pIp->mAttitude), .pSCtrl =  &(pIp->mController[0]), .max =  0.8f);
	IPCALL(ipLimitCtrlAngleInput);

    /*@ 
      ensures \valid(&(pIp->mAttitude)); 
      ensures \valid(&(pIp->mController[0])); 
    */
    IPCREATE(LimitCtrlRateInput, ipLimitCtrlRateInput, .pSA = &(pIp->mAttitude), .pSCtrl =  &(pIp->mController[0]), .max =  1.2f);
    IPCALL(ipLimitCtrlRateInput);

    return ;
}
