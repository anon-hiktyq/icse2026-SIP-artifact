#include "luaL_getmetafield.h"
void luaL_getmetafieldFun(void *p) 
{
    luaL_getmetafield *pIp = (luaL_getmetafield*)p;
  {int lua_getmetatable_ret_2;IPCALL(lua_getmetatable,iplua_getmetatable_0,.ret = pIp->&lua_getmetatable_ret_2);if (!(lua_getmetatable_ret_2)  /* no metatable? */
    *(pIp -> ret) = LUA_TNIL;
  else {
    int tt;
    {const char * lua_pushstring_ret_1;IPCALL(lua_pushstring,iplua_pushstring_0,.ret = pIp->lua_pushstring_ret_1);}
    {int lua_rawget_ret_0;IPCALL(lua_rawget,iplua_rawget_0,.ret = pIp->&lua_rawget_ret_0);tt = lua_rawget_ret_0;}
    if (tt == LUA_TNIL)  /* is metafield nil? */
      lua_pop(pIp -> L, 2);  /* remove metatable and metafield */
    else
      {IPCALL(lua_rotate,iplua_rotate_0);}  /* remove only metatable */
    *(pIp -> ret) = tt; /* return metafield type */
  }}
}