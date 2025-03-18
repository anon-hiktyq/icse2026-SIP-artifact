#include "findlast.h"
void findlastFun(findlast *pIp) 
{
  while (*(pIp ->p) != NULL)
    pIp -> p = &(*(pIp -> p))->next;
  pIp -> ret = pIp -> p;
}