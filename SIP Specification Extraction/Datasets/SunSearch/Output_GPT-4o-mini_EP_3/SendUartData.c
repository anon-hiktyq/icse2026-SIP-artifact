
#include "SendUartData.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->data + (0..pIp->len - 1));
  requires pIp->len >= 0;
  assigns \nothing; // No direct assignment to pIp->addr, but it is modified indirectly
*/
void SendUartDataFun(SendUartData *pIp)
{
    /*@ loop invariant 0 <= i <= pIp->len;
        loop assigns \nothing; // No direct assignment, but data is written to
        loop variant pIp->len - i; 
    */
    for (uint32_t i = 0; i < pIp->len; i++)
    {
        ADDR_WRITE(pIp->addr, pIp->data[i]);
    }
    return;
}
