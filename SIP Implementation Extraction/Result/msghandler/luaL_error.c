#include "luaL_error.h"
void luaL_errorFun(void *p) 
{
    luaL_error *pIp = (luaL_error*)p;
  va_list argp;
  va_start(argp, pIp -> fmt);
  {IPCALL(luaL_where,ipluaL_where_0,.L = pIp->L,.level = 1);}
  {const char * lua_pushvfstring_ret_0;IPCALL(lua_pushvfstring,iplua_pushvfstring_0,.ret = pIp->lua_pushvfstring_ret_0);}
  va_end(argp);
  {IPCALL(lua_concat,iplua_concat_0);}
  *(pIp -> ret) = lua_error(L);
}