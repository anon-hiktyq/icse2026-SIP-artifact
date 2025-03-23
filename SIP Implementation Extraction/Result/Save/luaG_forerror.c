#include "luaG_forerror.h"
void luaG_forerrorFun(void *p) 
{
    luaG_forerror *pIp = (luaG_forerror*)p;
  {const char * luaT_objtypename_ret_0;IPCALL(luaT_objtypename,ipluaT_objtypename_0,.L = pIp->L,.o = pIp->o,.ret = luaT_objtypename_ret_0);IPCALL(luaG_runerror,ipluaG_runerror_0,.pIp->L = pIp->pIp->L,.fmt = "bad 'for' %s (number expected, got %s)");}
}