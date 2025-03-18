#include "lua_newuserdatauv.h"
void lua_newuserdatauvFun(void *p) 
{
    lua_newuserdatauv *pIp = (lua_newuserdatauv*)p;
  Udata *u;
  lua_lock(pIp -> L);
  api_check(pIp -> L, 0 <= pIp -> nuvalue && pIp -> nuvalue < SHRT_MAX, "invalid value");
  {Udata * luaS_newudata_ret_0;IPCALL(luaS_newudata,ipluaS_newudata_0,.ret = pIp->luaS_newudata_ret_0);u = luaS_newudata_ret_0;}
  setuvalue(pIp -> L, s2v(pIp -> L->top.p), u);
  api_incr_top(pIp -> L);
  luaC_checkGC(pIp -> L);
  lua_unlock(pIp -> L);
  pIp -> ret = getudatamem(u);
}