#include "lua_next.h"
void lua_nextFun(void *p) 
{
    lua_next *pIp = (lua_next*)p;
  Table *t;
  int more;
  {lua_lock(pIp->L);}
  {api_checkpop(pIp->L, 1);}
  {Table * gettable_ret_0;IPCALL(gettable,ipgettable_0,.L = pIp->L,.idx = pIp->idx,.ret = gettable_ret_0);t = gettable_ret_0;}
  {int luaH_next_ret_0;IPCALL(luaH_next,ipluaH_next_0,.ret = &luaH_next_ret_0);more = luaH_next_ret_0;}
  if (more)
    {api_incr_top(pIp->L);}
  else  /* no more elements */
    (pIp->L)->top.p--;  /* pop key */
  {lua_unlock(pIp->L);}
  *(pIp->ret) =  more;
}