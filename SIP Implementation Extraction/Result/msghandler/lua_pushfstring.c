#include "lua_pushfstring.h"
void lua_pushfstringFun(void *p) 
{
    lua_pushfstring *pIp = (lua_pushfstring*)p;
  const char *(pIp->ret);
  va_list argp;
  {lua_lock(pIp->L);}
  va_start(argp, (pIp->fmt));
  {const char * luaO_pushvfstring_ret_0;IPCALL(luaO_pushvfstring,ipluaO_pushvfstring_0,.ret = luaO_pushvfstring_ret_0);pIp->ret = luaO_pushvfstring_ret_0;}
  va_end(argp);
  {luaC_checkGC(pIp->L);}
  if ((pIp->ret) == NULL)  /* error? */
    {IPCALL(luaD_throw,ipluaD_throw_0);}
  {lua_unlock(pIp->L);}
  pIp->ret =  (pIp->ret);
}