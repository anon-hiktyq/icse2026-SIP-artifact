#include "newbox.h"
void newboxFun(void *p) 
{
    newbox *pIp = (newbox*)p;
  UBox box;{void * lua_newuserdatauv_ret_0; IPCALL(lua_newuserdatauv,iplua_newuserdatauv_0,.ret = lua_newuserdatauv_ret_0);box = (UBox *)lua_newuserdatauv_ret_0;}
  box->box = NULL;
  box->bsize = 0;
  {int luaL_newmetatable_ret_0;IPCALL(luaL_newmetatable,ipluaL_newmetatable_0,.L = pIp->L,.tname = "_UBOX*",.ret = &luaL_newmetatable_ret_0);if (luaL_newmetatable_ret_0)  /* creating metatable? */
    {IPCALL(luaL_setfuncs,ipluaL_setfuncs_0,.L = pIp->L,.l = boxmt,.nup = 0);}}  /* set its metamethods */
  {int lua_setmetatable_ret_0;IPCALL(lua_setmetatable,iplua_setmetatable_0,.ret = &lua_setmetatable_ret_0);lua_setmetatable_ret_0;}
}