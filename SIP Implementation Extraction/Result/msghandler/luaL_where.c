#include "luaL_where.h"
void luaL_whereFun(void *p) 
{
    luaL_where *pIp = (luaL_where*)p;
  lua_Debug ar;
  {int lua_getstack_ret_3;IPCALL(lua_getstack,iplua_getstack_0,.ret = &lua_getstack_ret_3);if ((lua_getstack_ret_3) {  /* check function at pIp -> level */
    {int lua_getinfo_ret_2;IPCALL(lua_getinfo,iplua_getinfo_0,.ret = &lua_getinfo_ret_2);}  /* get info about it */
    if (ar.currentline > 0) {  /* is there info? */
      {const char * lua_pushfstring_ret_1;IPCALL(lua_pushfstring,iplua_pushfstring_1,.ret = lua_pushfstring_ret_1);}
      return;
    }
  }}
  {const char * lua_pushfstring_ret_0;IPCALL(lua_pushfstring,iplua_pushfstring_0,.ret = lua_pushfstring_ret_0);}  /* else, no information available... */
}