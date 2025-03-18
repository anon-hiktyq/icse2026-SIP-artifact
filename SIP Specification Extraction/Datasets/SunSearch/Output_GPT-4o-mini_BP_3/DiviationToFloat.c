
#include "DiviationToFloat.h"

/*@ 
  requires pIp != NULL; 
  requires \valid(pIp);
  requires \valid(pIp->ret);
  requires \valid(pIp->input);
  requires \valid(pIp->mask);
  requires \valid(pIp->offset);
  requires \valid(pIp->LSB);
  assigns pIp->fresult, *(pIp->ret);
  ensures pIp->fresult == ((siint16)((pIp->input & pIp->mask) - pIp->offset)) * pIp->LSB);
  ensures *(pIp->ret) == pIp->fresult;
*/
void DiviationToFloatFun(DiviationToFloat *pIp)
{
    pIp->fresult = ((siint16)((pIp->input & pIp->mask) - pIp->offset)) * pIp->LSB;
    *(pIp->ret) = pIp->fresult;
}
