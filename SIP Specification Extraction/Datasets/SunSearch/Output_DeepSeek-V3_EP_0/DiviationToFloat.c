
#include "DiviationToFloat.h"

/*@ axiomatic Sum_array {
      logic integer sum(int* array, integer begin, integer end) reads array[begin .. (end-1)];
      axiom empty:
        \forall int* a, integer b, e; b >= e ==> sum(a,b,e) == 0;
      axiom range:
        \forall int* a, integer b, e; b < e ==> sum(a,b,e) == sum(a,b,e-1) + a[e-1];
   }
*/

/*@ requires \valid(pIp);
    requires \valid(pIp->ret);
    ensures pIp->fresult == \old((siint16)((pIp->input & pIp->mask) - pIp->offset)) * pIp->LSB;
    ensures *(pIp->ret) == pIp->fresult;
    assigns pIp->fresult, *(pIp->ret);
*/
void DiviationToFloatFun(DiviationToFloat *pIp)
{
    /*@ assert \valid(pIp) && \valid(pIp->ret); */
    pIp->fresult = ((siint16)((pIp->input & pIp->mask) - pIp->offset)) * pIp->LSB;

    *(pIp->ret) = pIp->fresult;
}
