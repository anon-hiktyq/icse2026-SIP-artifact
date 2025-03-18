
#include "checkrange.h"

/*@
  requires \valid(pIp) && \valid(pIp->ret);
  assigns *(pIp->ret);
  ensures (pIp->k - 1u < pIp->limit) ==> *(pIp->ret) == pIp->k;
  ensures (pIp->k - 1u >= pIp->limit) ==> *(pIp->ret) == 0;
*/
void checkrangeFun(checkrange *pIp) 
{
  *(pIp -> ret) = (pIp->k - 1u < pIp->limit) ? pIp->k : 0;
}
