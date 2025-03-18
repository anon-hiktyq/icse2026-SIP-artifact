#include "concretesize.h"
void concretesizeFun(concretesize *pIp) 
{
  if (pIp -> size == 0)
    *(pIp -> ret) = 0;
  else  /* space for the two arrays plus an unsigned in between */
    *(pIp -> ret) = pIp->size * (sizeof(Value) + 1) + sizeof(unsigned);
}