
#include "SendUartData.h"

/*@ axiomatic Sum_array {
      logic integer sum(int* array, integer begin, integer end) reads array[begin .. (end-1)];
      axiom empty:
         \forall int* a, integer b, e; b >= e ==> sum(a,b,e) == 0;
      axiom range:
         \forall int* a, integer b, e; b < e ==> sum(a,b,e) == sum(a,b,e-1) + a[e-1];
   }
*/

/*@ requires \valid(pIp);
    requires \valid(pIp->data + (0 .. pIp->len-1));
    assigns pIp->addr;
    ensures \forall unint32 i; 0 <= i < pIp->len ==> ADDR_WRITE(pIp->addr, pIp->data[i]);
*/
void SendUartDataFun(SendUartData *pIp)
{
    unint32 i;
    /*@ loop invariant 0 <= i <= pIp->len;
        loop invariant \forall unint32 j; 0 <= j < i ==> ADDR_WRITE(pIp->addr, pIp->data[j]);
        loop assigns pIp->addr;
        loop variant pIp->len - i;
    */
    for (i = 0; i < pIp->len; i++)
    {
        ADDR_WRITE(pIp->addr, pIp->data[i]);
    }
    return;
}
