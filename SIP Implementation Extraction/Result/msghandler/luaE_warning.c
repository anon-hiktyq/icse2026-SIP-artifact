#include "luaE_warning.h"
void luaE_warningFun(void *p) 
{
    luaE_warning *pIp = (luaE_warning*)p;
  lua_WarnFunction wf;{wf = G(pIp->L)->warnf;}
  if (wf != NULL)
    {wf(G(pIp->L)->ud_warn, pIp->msg, pIp->tocont);}
}