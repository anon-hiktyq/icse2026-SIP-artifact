#include "luaG_ordererror.h"
void luaG_ordererrorFun(void *p) 
{
    luaG_ordererror *pIp = (luaG_ordererror*)p;
  const char *t1;{const char * luaT_objtypename_ret_1;IPCALL(luaT_objtypename,ipluaT_objtypename_1,.ret = luaT_objtypename_ret_1);*t1 = luaT_objtypename_ret_1}
  const char *t2;{const char * luaT_objtypename_ret_0;IPCALL(luaT_objtypename,ipluaT_objtypename_0,.ret = luaT_objtypename_ret_0);*t2 = luaT_objtypename_ret_0}
  if (strcmp(t1, t2) == 0)
    luaG_runerror(pIp -> L, "attempt to compare two %s values", t1);
  else
    {IPCALL(luaG_runerror,ipluaG_runerror_0,.L = pIp->L,.fmt = "attempt to compare %s with %s");}
}