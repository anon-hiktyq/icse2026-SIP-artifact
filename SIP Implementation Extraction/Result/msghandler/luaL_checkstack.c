#include "luaL_checkstack.h"
void luaL_checkstackFun(void *p) 
{
    luaL_checkstack *pIp = (luaL_checkstack*)p;
  if (l_unlikely(!lua_checkstack(pIp -> L, pIp -> space))) {
    if (pIp -> msg)
      luaL_error(pIp -> L, "stack overflow (%s)", pIp -> msg);
    else
      {int luaL_error_ret_0;IPCALL(luaL_error,ipluaL_error_0,.L = pIp->L,.fmt = "stack overflow",.ret = &luaL_error_ret_0);}
  }
}