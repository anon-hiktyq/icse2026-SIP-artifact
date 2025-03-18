#include "lua_pushlstring.h"
void lua_pushlstringFun(void *p) 
{
    lua_pushlstring *pIp = (lua_pushlstring*)p;
  TString *ts;
  lua_lock(pIp -> L);
  {TString * luaS_new_ret_0;IPCALL(luaS_new,ipluaS_new_0,.ret = pIp->luaS_new_ret_0);ts = (pIp->len == 0) ? luaS_new_ret_0 : luaS_newlstr(pIp->L, pIp->s, pIp->len);}
  setsvalue2s(pIp -> L, pIp -> L->top.p, ts);
  api_incr_top(pIp -> L);
  luaC_checkGC(pIp -> L);
  lua_unlock(pIp -> L);
  pIp -> ret = getstr(ts);
}