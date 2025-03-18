
#include "DiviationToFloat.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->ret);
  requires \valid(pIp->input);
  requires \valid(pIp->mask);
  requires \valid(pIp->offset);
  requires \valid(pIp->LSB);
  assigns pIp->fresult, *(pIp->ret);
  ensures *(pIp->ret) == \old(pIp->fresult);
*/
void DiviationToFloatFun(DiviationToFloat *pIp)
{
    /*@ loop invariant \valid(pIp);
        loop assigns pIp->fresult;
        loop variant 0; 
    */
    pIp->fresult = ((siint16)((pIp->input & pIp->mask) - pIp->offset)) * pIp->LSB;

    *(pIp->ret) = pIp->fresult;
}
