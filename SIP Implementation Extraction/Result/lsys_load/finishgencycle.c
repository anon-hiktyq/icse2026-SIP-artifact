#include "finishgencycle.h"
void finishgencycleFun(void *p) 
{
    finishgencycle *pIp = (finishgencycle*)p;
  {IPCALL(correctgraylists,ipcorrectgraylists_0,.g = pIp->g);}
  {IPCALL(checkSizes,ipcheckSizes_0,.L = pIp->L,.g = pIp->g);}
  pIp -> g->gcstate = GCSpropagate;  /* skip restart */
  if (!pIp -> g->gcemergency)
    {IPCALL(callallpendingfinalizers,ipcallallpendingfinalizers_0,.L = pIp->L);}
}