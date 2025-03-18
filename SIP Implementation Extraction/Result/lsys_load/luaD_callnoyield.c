#include "luaD_callnoyield.h"
void luaD_callnoyieldFun(void *p) 
{
    luaD_callnoyield *pIp = (luaD_callnoyield*)p;
  {IPCALL(ccall,ipccall_0,.L = pIp->L,.func = pIp->func,.nResults = pIp->nResults,.inc = nyci);}
}