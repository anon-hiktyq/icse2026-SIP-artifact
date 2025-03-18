#include "concretesize.h"
void concretesizeFun(void *p) 
{
    concretesize *pIp = (concretesize*)p;
  if (pIp -> size == 0)
    *(pIp -> ret) = 0;
  else  /* space for the two arrays plus an unsigned in between */
    *(pIp -> ret) = size * (sizeof(Value) + 1) + sizeof(unsigned);
}