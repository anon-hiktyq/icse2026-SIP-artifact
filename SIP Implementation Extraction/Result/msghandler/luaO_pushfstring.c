#include "luaO_pushfstring.h"
void luaO_pushfstringFun(void *p) 
{
    luaO_pushfstring *pIp = (luaO_pushfstring*)p;
  const char *msg;
  va_list argp;
  va_start(argp, (pIp->fmt));
  {const char * luaO_pushvfstring_ret_0;IPCALL(luaO_pushvfstring,ipluaO_pushvfstring_0,.L = pIp->L,.fmt = pIp->fmt,.argp = argp,.ret = luaO_pushvfstring_ret_0);msg = luaO_pushvfstring_ret_0;}
  va_end(argp);
  if (msg == NULL)  /* error? */
    {IPCALL(luaD_throw,ipluaD_throw_0);}
  pIp->ret =  msg;
}