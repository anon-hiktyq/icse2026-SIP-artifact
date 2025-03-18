
#include "DiviationToFloat.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->ret);
  requires \valid(pIp->input); // Assuming input is a pointer
  requires \valid(pIp->mask); // Assuming mask is a pointer
  requires \valid(pIp->offset); // Assuming offset is a pointer
  requires \valid(pIp->LSB); // Assuming LSB is a pointer
  ensures \valid(pIp->ret);
  assigns pIp->fresult, *(pIp->ret);
*/
void DiviationToFloatFun(DiviationToFloat *pIp)
{
    pIp -> fresult = ((siint16)((pIp -> input & pIp -> mask) - pIp -> offset)) * pIp -> LSB ;

    *(pIp -> ret) = pIp -> fresult;
}
