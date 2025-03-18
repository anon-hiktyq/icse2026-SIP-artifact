#include "findlast.h"
void findlastFun(void *p) 
{
    findlast *pIp = (findlast*)p;
  while (pIp -> *p != NULL)
    pIp -> p = &(pIp -> *p)->next;
  pIp -> ret = p;
}