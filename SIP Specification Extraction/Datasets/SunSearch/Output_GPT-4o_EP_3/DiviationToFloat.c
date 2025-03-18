
#include "DiviationToFloat.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->ret);
  assigns pIp->fresult;
  assigns *(pIp->ret);
  ensures pIp->fresult == ((siint16)((pIp->input & pIp->mask) - pIp->offset)) * pIp->LSB;
  ensures *(pIp->ret) == pIp->fresult;
*/
void DiviationToFloatFun(DiviationToFloat *pIp)
{
    pIp->fresult = ((siint16)((pIp->input & pIp->mask) - pIp->offset)) * pIp->LSB;
    *(pIp->ret) = pIp->fresult;
}
