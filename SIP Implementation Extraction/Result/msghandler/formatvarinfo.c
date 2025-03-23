#include "formatvarinfo.h"
void formatvarinfoFun(void *p) 
{
    formatvarinfo *pIp = (formatvarinfo*)p;
  if ((pIp->kind) == NULL)
    pIp->ret =  "";  /* no information */
  else
    const char * luaO_pushfstring_ret_0;IPCALL(luaO_pushfstring,ipluaO_pushfstring_0,.ret = luaO_pushfstring_ret_0);pIp->ret =  luaO_pushfstring_ret_0;
}