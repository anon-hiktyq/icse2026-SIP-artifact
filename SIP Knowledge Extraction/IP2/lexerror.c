#include "lexerror.h"
void lexerrorFun(void *p) 
{
    lexerror *pIp = (lexerror*)p;
  {const char * luaG_addinfo_ret_1;IPCALL(luaG_addinfo,ipluaG_addinfo_0,.ret = luaG_addinfo_ret_1);pIp->msg = luaG_addinfo_ret_1;}
  if (pIp -> token)
    {const char * luaO_pushfstring_ret_0;IPCALL(luaO_pushfstring,ipluaO_pushfstring_0,.ret = luaO_pushfstring_ret_0);}
  {IPCALL(luaD_throw,ipluaD_throw_0);}
}