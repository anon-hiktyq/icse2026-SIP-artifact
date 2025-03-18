
#include "isneg.h"

/*@
  requires \valid(pIp) && \valid(pIp->s) && \valid(pIp->ret);
  requires \valid(*(pIp->s));
  assigns pIp->s, *(pIp->ret);
  ensures **(pIp->s) == '-' ==> *(pIp->ret) == 0;
  ensures **(pIp->s) == '+' ==> *(pIp->ret) == 0;
  ensures **(pIp->s) != '-' && **(pIp->s) != '+' ==> *(pIp->ret) == 0;
*/
void isnegFun(isneg *pIp) 
{
  if (**(pIp -> s) == '-') { 
    *(pIp -> s)++; 
  }
  else if (**(pIp -> s) == '+') {
    *(pIp -> s)++;
  }
  *(pIp -> ret) = 0;
  /*@ assert *(pIp->ret) == 0; */
}
