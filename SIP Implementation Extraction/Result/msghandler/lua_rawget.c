#include "lua_rawget.h"
void lua_rawgetFun(void *p) 
{
    lua_rawget *pIp = (lua_rawget*)p;
  Table *t;
  lu_byte tag;
  lua_lock(pIp -> L);
  api_checkpop(pIp -> L, 1);
  {Table * gettable_ret_1;IPCALL(gettable,ipgettable_0,.L = pIp->L,.idx = pIp->idx,.ret = pIp->gettable_ret_1);t = gettable_ret_1;}
  {lu_byte luaH_get_ret_0;IPCALL(luaH_get,ipluaH_get_0,.ret = pIp->&luaH_get_ret_0);tag = luaH_get_ret_0;}
  pIp -> L->top.p--;  /* pop key */
  *(pIp -> ret) = finishrawget(L, tag);
}