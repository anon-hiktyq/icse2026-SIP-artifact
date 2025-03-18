#include "formatvarinfo.h"
void formatvarinfoFun(void *p) 
{
    formatvarinfo *pIp = (formatvarinfo*)p;

  if (pIp -> kind == NULL)
    pIp -> ret = ""; /* no information */
  else
    pIp -> {const char * luaO_pushfstring_ret_0;IPCALL(luaO_pushfstring,ipluaO_pushfstring_0,.ret = pIp->luaO_pushfstring_ret_0);}name);
}