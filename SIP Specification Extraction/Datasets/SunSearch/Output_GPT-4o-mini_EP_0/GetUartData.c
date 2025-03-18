
#include "GetUartData.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->ret);
  requires \valid(pIp->data + (0..pIp->len - 1));
  requires pIp->len > 0;
  ensures \result == pIp->bSucc;
  assigns pIp->bSucc, pIp->data[0..pIp->len - 1], *(pIp->ret);
*/
void GetUartDataFun(GetUartData *pIp)
{
    /*@ loop invariant 0 <= i <= pIp->len;
        loop variant pIp->len - i; 
    */
    for (unint32 i = 0; i < pIp->len; i++)
    {
        pIp->data[i] = ADDR_READ(pIp->addr);
    }

    unint32 fifoCnt;
    fifoCnt = ADDR_READ(0x88D0);
    pIp->bSucc = 0;

    if (fifoCnt == pIp->len)
    {
        pIp->bSucc = 1;
    }

    *(pIp->ret) = pIp->bSucc;
}
