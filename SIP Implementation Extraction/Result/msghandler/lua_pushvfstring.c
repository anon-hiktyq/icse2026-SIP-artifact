#include "lua_pushvfstring.h"
void lua_pushvfstringFun(void *p) 
{
    lua_pushvfstring *pIp = (lua_pushvfstring*)p;
  const char *(pIp->ret);
  {lua_lock(pIp->L);}
  {const char * luaO_pushvfstring_ret_0;IPCALL(luaO_pushvfstring,ipluaO_pushvfstring_0,.ret = luaO_pushvfstring_ret_0);pIp->ret = luaO_pushvfstring_ret_0;}
  {luaC_checkGC(pIp->L);}
  {lua_unlock(pIp->L);}
  pIp->ret =  (pIp->ret);
}