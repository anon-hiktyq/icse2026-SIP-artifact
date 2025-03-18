#include "panic.h"
void panicFun(void *p) 
{
    panic *pIp = (panic*)p;
  const char *msg;{int lua_type_ret_0;IPCALL(lua_type,iplua_type_0,.ret = pIp->&lua_type_ret_0);*msg = (lua_type_ret_0}


  lua_writestringerror("PANIC: unprotected error in call to Lua API (%s)\n",
                        msg);
  *(pIp -> ret) = 0; /* return to Lua to abort */
}