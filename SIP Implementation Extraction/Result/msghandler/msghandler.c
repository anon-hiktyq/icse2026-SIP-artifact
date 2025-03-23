#include "msghandler.h"
void msghandlerFun(void *p) 
{
    msghandler *pIp = (msghandler*)p;
  const char msg;{msg = lua_tostring(pIp->L, 1);}
  if (msg == NULL) {  /* is error object not a string? */
    {int lua_type_ret_0;IPCALL(lua_type,iplua_type_0,.ret = &lua_type_ret_0);if (luaL_callmeta(pIp->L, 1, "__tostring") &&  /* does it have a metamethod */
        lua_type_ret_0 == LUA_TSTRING)  /* that produces a string? */
      *(pIp->ret) =  1;  /* that is the message */
    else
      {msg = lua_pushfstring(pIp->L, "(error object is a %s value)",
                               luaL_typename(pIp->L, 1));}}
  }
  {IPCALL(luaL_traceback,ipluaL_traceback_0);}  /* append a standard traceback */
  *(pIp->ret) =  1;  /* return the traceback */
}