
#include "SendUartData.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->data + (0 .. pIp->len - 1));
  requires pIp->len >= 0;
  assigns pIp->addr[0 .. pIp->len - 1];
*/
void SendUartDataFun(SendUartData *pIp)
{
    unint32 i;

    /*@ 
      loop invariant 0 <= i <= pIp->len;
      loop invariant \forall integer k; 0 <= k < i ==> ADDR_WRITE(pIp->addr, pIp->data[k]);
      loop assigns i, pIp->addr[0 .. pIp->len - 1];
      loop variant pIp->len - i;
    */
    for (i = 0; i < pIp->len; i++)
    {
        ADDR_WRITE(pIp->addr, pIp->data[i]);
    }
    return;
}
