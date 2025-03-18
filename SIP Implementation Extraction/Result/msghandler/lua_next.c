#include "lua_next.h"
void lua_nextFun(void *p) 
{
    lua_next *pIp = (lua_next*)p;
  Table *t;
  int pIp -> more;
  lua_lock(pIp -> L);
  api_checkpop(pIp -> L, 1);
  {Table * gettable_ret_1;IPCALL(gettable,ipgettable_0,.L = pIp->L,.idx = pIp->idx,.ret = pIp->gettable_ret_1);t = gettable_ret_1;}
  {int luaH_next_ret_0;IPCALL(luaH_next,ipluaH_next_0,.ret = pIp->&luaH_next_ret_0);pIp->more = luaH_next_ret_0;}
  if (pIp -> more)
    api_incr_top(pIp -> L);
  else  /* no pIp -> more elements */
    pIp -> L->top.p--;  /* pop key */
  lua_unlock(pIp -> L);
  *(pIp -> ret) = more;
}