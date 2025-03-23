#include "luaL_where.h"
void luaL_whereFun(void *p) 
{
    luaL_where *pIp = (luaL_where*)p;
  lua_Debug ar;
  {int lua_getstack_ret_0;IPCALL(lua_getstack,iplua_getstack_0,.ret = &lua_getstack_ret_0);if (lua_getstack_ret_0) {  /* check function at level */
    {int lua_getinfo_ret_0;IPCALL(lua_getinfo,iplua_getinfo_0,.ret = &lua_getinfo_ret_0);lua_getinfo_ret_0;}  /* get info about it */
    if (ar.currentline > 0) {  /* is there info? */
      {const char * lua_pushfstring_ret_0;IPCALL(lua_pushfstring,iplua_pushfstring_0,.ret = lua_pushfstring_ret_0);lua_pushfstring_ret_0;}
      return;
    }
  }}
  {const char * lua_pushfstring_ret_1;IPCALL(lua_pushfstring,iplua_pushfstring_1,.ret = lua_pushfstring_ret_1);lua_pushfstring_ret_1;}  /* else, no information available... */
}