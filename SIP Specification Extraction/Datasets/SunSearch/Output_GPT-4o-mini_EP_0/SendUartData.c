
#include "SendUartData.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->data + (0..pIp->len - 1));
  requires pIp->len >= 0;
  assigns pIp->addr; // Assuming ADDR_WRITE modifies the address
*/
void SendUartDataFun(SendUartData *pIp)
{
    /*@ loop invariant 0 <= i <= pIp->len;
        loop assigns pIp->addr;
        loop variant pIp->len - i;
    */
    for (unint32 i = 0; i < pIp->len; i++)
    {
        ADDR_WRITE(pIp->addr, pIp->data[i]);
    }
    return;
}
