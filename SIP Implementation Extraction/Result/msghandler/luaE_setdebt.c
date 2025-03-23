#include "luaE_setdebt.h"
void luaE_setdebtFun(void *p) 
{
    luaE_setdebt *pIp = (luaE_setdebt*)p;
  l_mem tb;{tb = gettotalbytes(pIp->g);}
  {lua_assert(tb > 0);}
  if ((pIp->debt) > MAX_LMEM - tb)
    (pIp->debt) = MAX_LMEM - tb;  /* will make GCtotalbytes == MAX_LMEM */
  (pIp->g)->GCtotalbytes = tb + (pIp->debt);
  (pIp->g)->GCdebt = (pIp->debt);
}