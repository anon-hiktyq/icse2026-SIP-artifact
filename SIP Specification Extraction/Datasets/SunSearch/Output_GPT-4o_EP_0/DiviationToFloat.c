
#include "DiviationToFloat.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->ret);
  ensures *(pIp->ret) == ((siint16)((pIp->input & pIp->mask) - pIp->offset)) * pIp->LSB;
  assigns pIp->fresult, *(pIp->ret);
*/
void DiviationToFloatFun(DiviationToFloat *pIp)
{
    /*@ 
      requires \valid(pIp);
      requires \valid(pIp->ret);
      assigns pIp->fresult, *(pIp->ret);
      ensures pIp->fresult == ((siint16)((pIp->input & pIp->mask) - pIp->offset)) * pIp->LSB;
      ensures *(pIp->ret) == pIp->fresult;
    */
    pIp->fresult = ((siint16)((pIp->input & pIp->mask) - pIp->offset)) * pIp->LSB;

    *(pIp->ret) = pIp->fresult;
}
