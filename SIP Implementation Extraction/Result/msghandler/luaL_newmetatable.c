#include "luaL_newmetatable.h"
void luaL_newmetatableFun(void *p) 
{
    luaL_newmetatable *pIp = (luaL_newmetatable*)p;
  if (luaL_getmetatable(pIp -> L, pIp -> tname) != LUA_TNIL)  /* name already in use? */
    *(pIp -> ret) = 0; /* leave previous value on top, but return 0 */
  {IPCALL(lua_settop,iplua_settop_0);}
  {IPCALL(lua_createtable,iplua_createtable_0);}  /* create metatable */
  {const char * lua_pushstring_ret_0;IPCALL(lua_pushstring,iplua_pushstring_0,.ret = pIp->lua_pushstring_ret_0);}
  {IPCALL(lua_setfield,iplua_setfield_1);}  /* metatable.__name = pIp -> tname */
  {IPCALL(lua_pushvalue,iplua_pushvalue_0);}
  {IPCALL(lua_setfield,iplua_setfield_0);}  /* registry.name = metatable */
  *(pIp -> ret) = 1;
}