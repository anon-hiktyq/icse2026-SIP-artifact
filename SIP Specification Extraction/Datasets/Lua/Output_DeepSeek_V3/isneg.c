
#include "isneg.h"

/*@
  requires \valid(pIp) && \valid(pIp->s) && \valid(*(pIp->s));
  requires \valid(pIp->ret);
  assigns *(pIp->s), *(pIp->ret);
  ensures \old(**(pIp->s)) == '-' ==> *(pIp->ret) == 1;
  ensures \old(**(pIp->s)) == '+' ==> *(pIp->ret) == 0;
  ensures \old(**(pIp->s)) != '-' && \old(**(pIp->s)) != '+' ==> *(pIp->ret) == 0;
*/
void isnegFun(isneg *pIp) 
{
  if (**(pIp -> s) == '-') { 
    *(pIp -> s)++; 
    *(pIp -> ret) = 1; // Corrected to set ret instead of returning
  }
  else if (**(pIp -> s) == '+') {
    *(pIp -> s)++;
    *(pIp -> ret) = 0; // Explicitly set ret for clarity
  }
  else {
    *(pIp -> ret) = 0;
  }
}
