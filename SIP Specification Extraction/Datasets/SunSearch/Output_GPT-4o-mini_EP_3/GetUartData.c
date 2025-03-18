
#include "GetUartData.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->data + (0..pIp->len-1));
  requires \valid(pIp->ret);
  requires pIp->len > 0;
  ensures pIp->bSucc == 1 ==> \forall unsigned int i; 0 <= i < pIp->len ==> pIp->data[i] == ADDR_READ(pIp->addr + i);
  assigns pIp->bSucc, *(pIp->ret), pIp->data[0..pIp->len-1];
*/
void GetUartDataFun(GetUartData *pIp)
{
    unsigned int fifoCnt;
    unsigned int i;

    pIp->bSucc = 0;
    fifoCnt = ADDR_READ(0x88D0);

    if (fifoCnt == pIp->len)
    {
        /*@ loop invariant 0 <= i <= pIp->len;
            loop assigns pIp->data[i];
            loop variant pIp->len - i;
        */
        for (i = 0; i < pIp->len; i++)
        {
            pIp->data[i] = ADDR_READ(pIp->addr + i);
        }

        pIp->bSucc = 1;
    }

    *(pIp->ret) = pIp->bSucc;
}
