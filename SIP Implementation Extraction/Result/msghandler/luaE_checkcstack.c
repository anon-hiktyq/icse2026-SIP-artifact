#include "luaE_checkcstack.h"
void luaE_checkcstackFun(void *p) 
{
    luaE_checkcstack *pIp = (luaE_checkcstack*)p;
  if (getCcalls(pIp -> L) == LUAI_MAXCCALLS)
    luaG_runerror(pIp -> L, "C stack overflow");
  else if (getCcalls(pIp -> L) >= (LUAI_MAXCCALLS / 10 * 11))
    {IPCALL(luaD_throw,ipluaD_throw_0);}  /* error while handling stack error */
}