#include "luaG_concaterror.h"
void luaG_concaterrorFun(void *p) 
{
    luaG_concaterror *pIp = (luaG_concaterror*)p;
  if (ttisstring(pIp -> p1) || cvt2str(pIp -> p1)) pIp -> p1 = pIp -> p2;
  {IPCALL(luaG_typeerror,ipluaG_typeerror_0,.L = pIp->L,.o = p1,.op = "concatenate");}
}