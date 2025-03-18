#include "luaG_tointerror.h"
void luaG_tointerrorFun(void *p) 
{
    luaG_tointerror *pIp = (luaG_tointerror*)p;
  lua_Integer temp;
  {int luaV_tointegerns_ret_0;IPCALL(luaV_tointegerns,ipluaV_tointegerns_0,.ret = &luaV_tointegerns_ret_0);if (!(luaV_tointegerns_ret_0)
    pIp -> p2 = pIp -> p1}
  {const char * varinfo_ret_0;IPCALL(varinfo,ipvarinfo_0,.L = pIp->L,.o = p2,.ret = varinfo_ret_0);IPCALL(luaG_runerror,ipluaG_runerror_0,.L = pIp->L,.fmt = "number%s has no integer representation");}
}