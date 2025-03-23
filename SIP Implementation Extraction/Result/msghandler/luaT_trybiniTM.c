#include "luaT_trybiniTM.h"
void luaT_trybiniTMFun(void *p) 
{
    luaT_trybiniTM *pIp = (luaT_trybiniTM*)p;
  TValue aux;
  {setivalue(&aux, pIp->i2);}
  {IPCALL(luaT_trybinassocTM,ipluaT_trybinassocTM_0,.L = pIp->L,.p1 = pIp->p1,.p2 = &aux,.flip = pIp->flip,.res = pIp->res,.event = pIp->event);}
}