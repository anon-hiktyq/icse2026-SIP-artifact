
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
    assigns \nothing;
    ensures \forall unsigned int i; 0 <= i < pIp->len ==> pIp->data[i] == \old(pIp->data[i]);
*/
void SendUartDataFun(SendUartData *pIp)
{
    unsigned int i;
    /*@ loop invariant 0 <= i <= pIp->len;
        loop invariant \forall unsigned int j; 0 <= j < i ==> pIp->data[j] == pIp->data[j];
        loop assigns i;
        loop variant pIp->len - i;
    */
    for (i = 0; i < pIp->len; i++)
    {
        ADDR_WRITE(pIp->addr, pIp->data[i]);
    }
    return;
}
