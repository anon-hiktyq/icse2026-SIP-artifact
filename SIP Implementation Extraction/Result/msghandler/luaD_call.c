#include "luaD_call.h"
void luaD_callFun(void *p) 
{
    luaD_call *pIp = (luaD_call*)p;
  {IPCALL(ccall,ipccall_0,.L = pIp->L,.func = pIp->func,.nResults = pIp->nResults,.inc = 1);}
}