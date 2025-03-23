#include "lua_pushexternalstring.h"
void lua_pushexternalstringFun(void *p) 
{
    lua_pushexternalstring *pIp = (lua_pushexternalstring*)p;
  TString *ts;
  {lua_lock(pIp->L);}
  {api_check(pIp->L, pIp->len <= MAX_SIZE, "string too large");}
  {api_check(pIp->L, pIp->s[pIp->len] == '\0', "string not ending with zero");}
  {TString * luaS_newextlstr_ret_0;IPCALL(luaS_newextlstr,ipluaS_newextlstr_0,.ret = luaS_newextlstr_ret_0);ts = luaS_newextlstr_ret_0;}
  {setsvalue2s(pIp->L, pIp->L->top.p, ts);}
  {api_incr_top(pIp->L);}
  {luaC_checkGC(pIp->L);}
  {lua_unlock(pIp->L);}
  pIp->ret =  getstr(ts);
}