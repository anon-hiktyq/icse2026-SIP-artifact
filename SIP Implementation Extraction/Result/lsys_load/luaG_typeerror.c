#include "luaG_typeerror.h"
void luaG_typeerrorFun(void *p) 
{
    luaG_typeerror *pIp = (luaG_typeerror*)p;
  {const char * varinfo_ret_0;IPCALL(varinfo,ipvarinfo_0,.L = pIp->L,.o = pIp->o,.ret = varinfo_ret_0);IPCALL(typeerror,iptypeerror_0,.L = pIp->L,.o = pIp->o,.op = pIp->op,.extra = varinfo_ret_0);}
}