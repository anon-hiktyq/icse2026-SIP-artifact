#include "genlink.h"
void genlinkFun(void *p) 
{
    genlink *pIp = (genlink*)p;
  lua_assert(isblack(pIp -> o));
  if (getage(pIp -> o) == G_TOUCHED1) {  /* touched in this cycle? */
    linkobjgclist(pIp -> o, pIp -> g->grayagain);  /* link it back in 'grayagain' */
  }  /* everything else do not need to be linked back */
  else if (getage(pIp -> o) == G_TOUCHED2)
    setage(pIp -> o, G_OLD);  /* advance age */
}