#include "isneg.h"
void isnegFun(isneg *pIp) 
{
  if (**(pIp -> s)== '-') { *(pIp -> s)++; return 1; }
  else if (**(pIp -> s)== '+') *(pIp -> s)++;
  *(pIp -> ret) = 0;
}