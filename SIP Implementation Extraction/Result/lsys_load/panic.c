#include "panic.h"
void panicFun(void *p) 
{
    panic *pIp = (panic*)p;
  const char msg;{msg = (lua_type(pIp->L, -1) == LUA_TSTRING)
                  ? lua_tostring(pIp->L, -1)
                  : "error object is not a string";}
  {lua_writestringerror("PANIC: unprotected error in call to Lua API (%s)\n",
                        msg);}
  *(pIp->ret) =  0;  /* return to Lua to abort */
}