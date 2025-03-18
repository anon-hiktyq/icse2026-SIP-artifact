#include "isneg.h"
void isnegFun(void *p) 
{
    isneg *pIp = (isneg*)p;
  if (pIp -> **s == '-') { (pIp -> *s)++; return 1; }
  else if (pIp -> **s == '+') (pIp -> *s)++;
  *(pIp -> ret) = 0;
}