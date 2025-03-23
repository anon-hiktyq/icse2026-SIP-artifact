#include "callallpendingfinalizers.h"
void callallpendingfinalizersFun(void *p) 
{
    callallpendingfinalizers *pIp = (callallpendingfinalizers*)p;
  global_State g;{g = G(pIp->L);}
  while (g->tobefnz)
    {IPCALL(GCTM,ipGCTM_0,.L = pIp->L);}
}