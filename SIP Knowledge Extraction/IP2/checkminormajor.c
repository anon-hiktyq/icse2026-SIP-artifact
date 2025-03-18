#include "checkminormajor.h"
void checkminormajorFun(void *p) 
{
    checkminormajor *pIp = (checkminormajor*)p;
  l_mem limit = applygcparam(pIp -> g, MINORMAJOR, pIp -> g->GCmajorminor);
  if (limit == 0)
    *(pIp -> ret) = 0; /* special case: 'minormajor' 0 stops major collections */
  *(pIp -> ret) = (g->GCmarked >= limit);
}