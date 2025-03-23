#include "luaL_getmetafield.h"
void luaL_getmetafieldFun(void *p) 
{
    luaL_getmetafield *pIp = (luaL_getmetafield*)p;
  {int lua_getmetatable_ret_0;IPCALL(lua_getmetatable,iplua_getmetatable_0,.ret = &lua_getmetatable_ret_0);if (!lua_getmetatable_ret_0)  /* no metatable? */
    *(pIp->ret) =  LUA_TNIL;
  else {
    int tt;
    {const char * lua_pushstring_ret_0;IPCALL(lua_pushstring,iplua_pushstring_0,.ret = lua_pushstring_ret_0);lua_pushstring_ret_0;}
    {int lua_rawget_ret_0;IPCALL(lua_rawget,iplua_rawget_0,.ret = &lua_rawget_ret_0);tt = lua_rawget_ret_0;}
    if (tt == LUA_TNIL)  /* is metafield nil? */
      {lua_pop(pIp->L, 2);}  /* remove metatable and metafield */
    else
      {lua_remove(pIp->L, -2);}  /* remove only metatable */
    *(pIp->ret) =  tt;  /* return metafield type */
  }}
}