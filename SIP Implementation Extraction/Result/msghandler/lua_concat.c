#include "lua_concat.h"
void lua_concatFun(void *p) 
{
    lua_concat *pIp = (lua_concat*)p;
  lua_lock(pIp -> L);
  api_checknelems(pIp -> L, pIp -> n);
  if (pIp -> n > 0) {
    {IPCALL(luaV_concat,ipluaV_concat_0);}
    luaC_checkGC(pIp -> L);
  }
  else {  /* nothing to concatenate */
    setsvalue2s(pIp -> L, pIp -> L->top.p, luaS_newlstr(pIp -> L, "", 0));  /* push empty string */
    api_incr_top(pIp -> L);
  }
  lua_unlock(pIp -> L);
}