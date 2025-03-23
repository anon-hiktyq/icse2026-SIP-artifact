#include "luaG_callerror.h"
void luaG_callerrorFun(void *p) 
{
    luaG_callerror *pIp = (luaG_callerror*)p;
  CallInfo *ci = (pIp->L)->ci;
  const char *name = NULL;  /* to avoid warnings */
  const char kind;{const char * funcnamefromcall_ret_0; IPCALL(funcnamefromcall,ipfuncnamefromcall_0,.L = pIp->L,.ci = ci,.name = &name,.ret = funcnamefromcall_ret_0);kind = funcnamefromcall_ret_0;}
  const char extra;{const char * varinfo_ret_0; IPCALL(varinfo,ipvarinfo_0,.L = pIp->L,.o = pIp->o,.ret = varinfo_ret_0);extra = kind ? formatvarinfo(pIp->L, kind, name) : varinfo_ret_0;}
  {IPCALL(typeerror,iptypeerror_0,.L = pIp->L,.o = pIp->o,.op = "call",.extra = extra);}
}