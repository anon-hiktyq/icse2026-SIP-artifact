
#include "SendUartData.h"

/*@ requires pIp != NULL;
    requires pIp->len >= 0;
    requires \valid(pIp->data + (0..pIp->len - 1));
    assigns \nothing;
    ensures \forall integer j; 0 <= j < pIp->len ==> 
            \exists integer k; pIp->data[j] == pIp->data[k];
*/
void SendUartDataFun(SendUartData *pIp)
{
    /*@ loop invariant 0 <= i <= pIp->len;
        loop assigns i;
        loop variant pIp->len - i;
    */
    unsigned int i; // Changed uint32_t to unsigned int for compatibility
    for (i = 0; i < pIp->len; i++)
    {
        /*@ assert \valid(pIp->addr);
            assert \valid(pIp->data + i);
        */
        ADDR_WRITE(pIp->addr, pIp->data[i]);
    }
    return;
}
