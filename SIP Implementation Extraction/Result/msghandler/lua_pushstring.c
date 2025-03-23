#include "lua_pushstring.h"
void lua_pushstringFun(void *p) 
{
    lua_pushstring *pIp = (lua_pushstring*)p;
  {lua_lock(pIp->L);}
  if ((pIp->s) == NULL)
    {setnilvalue(s2v(pIp->L->top.p));}
  else {
    TString *ts;
    {TString * luaS_new_ret_0;IPCALL(luaS_new,ipluaS_new_0,.ret = luaS_new_ret_0);ts = luaS_new_ret_0;}
    {setsvalue2s(pIp->L, pIp->L->top.p, ts);}
    {pIp->s = getstr(ts);}  /* internal copy's address */
  }
  {api_incr_top(pIp->L);}
  {luaC_checkGC(pIp->L);}
  {lua_unlock(pIp->L);}
  pIp->ret =  (pIp->s);
}