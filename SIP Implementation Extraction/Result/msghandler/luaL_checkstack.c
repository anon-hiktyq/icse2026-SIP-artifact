#include "luaL_checkstack.h"
void luaL_checkstackFun(void *p) 
{
    luaL_checkstack *pIp = (luaL_checkstack*)p;
  {int lua_checkstack_ret_0;IPCALL(lua_checkstack,iplua_checkstack_0,.L = pIp->L,.n = pIp->space,.ret = &lua_checkstack_ret_0);if (l_unlikely(!lua_checkstack(pIp->L, pIp->space))) {
    if ((pIp->msg))
      {int luaL_error_ret_1;IPCALL(luaL_error,ipluaL_error_1,.pIp->L = pIp->pIp->L,.fmt = "stack overflow (%s)",.ret = &luaL_error_ret_1);luaL_error_ret_1;}
    else
      {int luaL_error_ret_0;IPCALL(luaL_error,ipluaL_error_0,.L = pIp->L,.fmt = "stack overflow",.ret = &luaL_error_ret_0);luaL_error_ret_0;}
  }}
}