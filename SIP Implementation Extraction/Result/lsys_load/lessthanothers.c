#include "lessthanothers.h"
void lessthanothersFun(void *p) 
{
    lessthanothers *pIp = (lessthanothers*)p;
  lua_assert(!ttisnumber(pIp -> l) || !ttisnumber(pIp -> r));
  if (ttisstring(pIp -> l) && ttisstring(pIp -> r))  /* both are strings? */
    *(pIp -> ret) = l_strcmp(tsvalue(l), tsvalue(r)) < 0;
  else
    *(pIp -{int luaT_callorderTM_ret_0;IPCALL(luaT_callorderTM,ipluaT_callorderTM_0,.ret = pIp->&luaT_callorderTM_ret_0);}, TM_LT);
}