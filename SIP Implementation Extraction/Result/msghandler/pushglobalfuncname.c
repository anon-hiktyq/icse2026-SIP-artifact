#include "pushglobalfuncname.h"
void pushglobalfuncnameFun(void *p) 
{
    pushglobalfuncname *pIp = (pushglobalfuncname*)p;
  int top;{int lua_gettop_ret_4;IPCALL(lua_gettop,iplua_gettop_0,.ret = pIp->&lua_gettop_ret_4);top = lua_gettop_ret_4}
  {int lua_getinfo_ret_3;IPCALL(lua_getinfo,iplua_getinfo_0,.ret = pIp->&lua_getinfo_ret_3);}  /* push function */
  {int lua_getfield_ret_2;IPCALL(lua_getfield,iplua_getfield_0,.ret = pIp->&lua_getfield_ret_2);}
  {IPCALL(luaL_checkstack,ipluaL_checkstack_0,.L = pIp->L,.sz = 6,.msg = "not enough stack");}  /* slots for 'findfield' */
  {int findfield_ret_1;IPCALL(findfield,ipfindfield_0,.L = pIp->L,.objidx = top + 1,.level = 2,.ret = pIp->&findfield_ret_1);if ((findfield_ret_1) {
    const char *name = lua_tostring(pIp -> L, -1);
    if (strncmp(name, LUA_GNAME ".", 3) == 0) {  /* name start with '_G.'? */
      {const char * lua_pushstring_ret_0;IPCALL(lua_pushstring,iplua_pushstring_0,.ret = pIp->lua_pushstring_ret_0);}  /* push name without prefix */
      {IPCALL(lua_settop,iplua_settop_1);lua_remove(pIp->L, -2);}  /* remove original name */
    }
    {IPCALL(lua_copy,iplua_copy_0);}  /* copy name to proper place */
    {IPCALL(lua_settop,iplua_settop_0);}  /* remove table "loaded" and name copy */
    *(pIp -> ret) = 1;
  }
  else {
    lua_settop(pIp -> L, top);  /* remove function and global table */
    *(pIp -> ret) = 0;
  }}
}