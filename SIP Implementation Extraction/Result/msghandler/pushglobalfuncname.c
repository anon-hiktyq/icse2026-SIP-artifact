#include "pushglobalfuncname.h"
void pushglobalfuncnameFun(void *p) 
{
    pushglobalfuncname *pIp = (pushglobalfuncname*)p;
  int top;{int lua_gettop_ret_0; IPCALL(lua_gettop,iplua_gettop_0,.ret = &lua_gettop_ret_0);top = lua_gettop_ret_0;}
  {int lua_getinfo_ret_0;IPCALL(lua_getinfo,iplua_getinfo_0,.ret = &lua_getinfo_ret_0);lua_getinfo_ret_0;}  /* push function */
  {int lua_getfield_ret_0;IPCALL(lua_getfield,iplua_getfield_0,.ret = &lua_getfield_ret_0);lua_getfield_ret_0;}
  {IPCALL(luaL_checkstack,ipluaL_checkstack_0,.L = pIp->L,.sz = 6,.msg = "not enough stack");}  /* slots for 'findfield' */
  {int findfield_ret_0;IPCALL(findfield,ipfindfield_0,.L = pIp->L,.objidx = top + 1,.level = 2,.ret = &findfield_ret_0);if (findfield_ret_0) {
    const char name;{name = lua_tostring(pIp->L, -1);}
    if (strncmp(name, LUA_GNAME ".", 3) == 0) {  /* name start with '_G.'? */
      {const char * lua_pushstring_ret_0;IPCALL(lua_pushstring,iplua_pushstring_0,.ret = lua_pushstring_ret_0);lua_pushstring_ret_0;}  /* push name without prefix */
      {lua_remove(pIp->L, -2);}  /* remove original name */
    }
    {IPCALL(lua_copy,iplua_copy_0);}  /* copy name to proper place */
    {IPCALL(lua_settop,iplua_settop_0);}  /* remove table "loaded" and name copy */
    *(pIp->ret) =  1;
  }
  else {
    {IPCALL(lua_settop,iplua_settop_1);}  /* remove function and global table */
    *(pIp->ret) =  0;
  }}
}