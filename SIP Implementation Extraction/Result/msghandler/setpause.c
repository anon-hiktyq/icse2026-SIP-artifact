#include "setpause.h"
void setpauseFun(void *p) 
{
    setpause *pIp = (setpause*)p;
  l_mem threshold;{threshold = applygcparam(pIp->g, PAUSE, pIp->g->GCmarked);}
  l_mem debt;{debt = threshold - gettotalbytes(pIp->g);}
  if (debt < 0) debt = 0;
  {IPCALL(luaE_setdebt,ipluaE_setdebt_0);}
}