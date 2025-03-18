#include "checkrange.h"
void checkrangeFun(checkrange *pIp) 
{
  *(pIp -> ret) = (pIp->k - 1u < pIp->limit) ? pIp->k : 0;
}