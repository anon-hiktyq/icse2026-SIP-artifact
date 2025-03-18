
#include "concretesize.h"

/*@
  requires \valid(pIp) && \valid(pIp->ret);
  assigns *(pIp->ret);
  ensures pIp->size == 0 ==> *(pIp->ret) == 0;
  ensures pIp->size != 0 ==> *(pIp->ret) == pIp->size * (sizeof(Value) + 1) + sizeof(unsigned);
*/
void concretesizeFun(concretesize *pIp) 
{
  if (pIp->size == 0)
    *(pIp->ret) = 0;
  else  /* space for the two arrays plus an unsigned in between */
    *(pIp->ret) = pIp->size * (sizeof(Value) + 1) + sizeof(unsigned);
}
