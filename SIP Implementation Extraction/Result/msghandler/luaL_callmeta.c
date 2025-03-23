#include "luaL_callmeta.h"
void luaL_callmetaFun(void *p) 
{
    luaL_callmeta *pIp = (luaL_callmeta*)p;
  {int lua_absindex_ret_0;IPCALL(lua_absindex,iplua_absindex_0,.ret = &lua_absindex_ret_0);pIp->obj = lua_absindex_ret_0;}
  {int luaL_getmetafield_ret_0;IPCALL(luaL_getmetafield,ipluaL_getmetafield_0,.L = pIp->L,.obj = pIp->obj,.event = pIp->event,.ret = &luaL_getmetafield_ret_0);if (luaL_getmetafield_ret_0 == LUA_TNIL)  /* no metafield? */
    *(pIp->ret) =  0;}
  {IPCALL(lua_pushvalue,iplua_pushvalue_0);}
  {lua_call(pIp->L, 1, 1);}
  *(pIp->ret) =  1;
}