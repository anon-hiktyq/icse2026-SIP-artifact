#include "typeerror.h"
void typeerrorFun(void *p) 
{
    typeerror *pIp = (typeerror*)p;

  const char *t;{const char * luaT_objtypename_ret_0;IPCALL(luaT_objtypename,ipluaT_objtypename_0,.ret = luaT_objtypename_ret_0);*t = luaT_objtypename_ret_0}
  {IPCALL(luaG_runerror,ipluaG_runerror_0,.L = pIp->L,.fmt = "attempt to %s a %s value%s");}
}