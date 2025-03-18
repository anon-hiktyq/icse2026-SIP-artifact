#include "luaG_callerror.h"
void luaG_callerrorFun(void *p) 
{
    luaG_callerror *pIp = (luaG_callerror*)p;
  CallInfo *ci = pIp -> L->ci;
  const char *name = NULL;  /* to avoid warnings */
  const char *kind;{const char * funcnamefromcall_ret_1;IPCALL(funcnamefromcall,ipfuncnamefromcall_0,.L = pIp->L,.ci = ci,.name = &name,.ret = funcnamefromcall_ret_1);*kind = funcnamefromcall_ret_1}
  const char *extra;{const char * formatvarinfo_ret_0;IPCALL(formatvarinfo,ipformatvarinfo_0,.L = pIp->L,.kind = kind,.name = name,.ret = formatvarinfo_ret_0);*extra = kind ? formatvarinfo_ret_0 : varinfo(pIp->L, pIp->o)}
  {IPCALL(typeerror,iptypeerror_0,.L = pIp->L,.o = pIp->o,.op = "call",.extra = extra);}
}