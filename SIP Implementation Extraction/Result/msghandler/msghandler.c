#include "msghandler.h"
void msghandlerFun(void *p) 
{
    msghandler *pIp = (msghandler*)p;
  const char *msg = lua_tostring(pIp -> L, 1);
  if (msg == NULL) {  /* is error object not a string? */
    {int luaL_callmeta_ret_1;IPCALL(luaL_callmeta,ipluaL_callmeta_0,.ret = pIp->&luaL_callmeta_ret_1);if ((luaL_callmeta_ret_1)&&  /* does it have a metamethod */
        lua_type(pIp -> L, -1) == LUA_TSTRING)  /* that produces a string? */
      *(pIp -> ret) = 1; /* that is the message */
    else
      msg = {const char * lua_pushfstring_ret_0;IPCALL(lua_pushfstring,iplua_pushfstring_0,.ret = pIp->lua_pushfstring_ret_0);}
}
  }
  {IPCALL(luaL_traceback,ipluaL_traceback_0);}  /* append a standard traceback */
  *(pIp -> ret) = 1; /* return the traceback */
}