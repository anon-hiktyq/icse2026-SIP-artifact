#include "luaT_trybinassocTM.h"
void luaT_trybinassocTMFun(void *p) 
{
    luaT_trybinassocTM *pIp = (luaT_trybinassocTM*)p;

  if (pIp -> flip)
    luaT_trybinTM(pIp -> L, pIp -> p2, pIp -> p1, pIp -> res, pIp -> event);
  else
    {IPCALL(luaT_trybinTM,ipluaT_trybinTM_0,.L = pIp->L,.p1 = pIp->p1,.p2 = pIp->p2,.res = pIp->res,.event = pIp->event);}
}