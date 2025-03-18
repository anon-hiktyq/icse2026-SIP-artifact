#include "lua_tolstring.h"
void lua_tolstringFun(void *p) 
{
    lua_tolstring *pIp = (lua_tolstring*)p;
  TValue *o;
  lua_lock(pIp -> L);
  {TValue * index2value_ret_1;IPCALL(index2value,ipindex2value_1,.L = pIp->L,.idx = pIp->idx,.ret = pIp->index2value_ret_1);o = index2value_ret_1;}
  if (!ttisstring(o)) {
    if (!cvt2str(o)) {  /* not convertible? */
      if pIp -> (len != NULL) *len = 0;
      lua_unlock(pIp -> L);
      pIp -> ret = NULL;
    }
    {IPCALL(luaO_tostring,ipluaO_tostring_0);}
    luaC_checkGC(pIp -> L);
    {TValue * index2value_ret_0;IPCALL(index2value,ipindex2value_0,.L = pIp->L,.idx = pIp->idx,.ret = pIp->index2value_ret_0);o = index2value_ret_0;}  /* previous call may reallocate the stack */
  }
  lua_unlock(pIp -> L);
  if (pIp -> len != NULL)
    pIp -> ret = getlstr(tsvalue(o), *len);
  else
    pIp -> ret = getstr(tsvalue(o));
}