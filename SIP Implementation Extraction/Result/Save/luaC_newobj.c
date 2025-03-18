#include "luaC_newobj.h"
void luaC_newobjFun(void *p) 
{
    luaC_newobj *pIp = (luaC_newobj*)p;
  pIp -> ret = luaC_newobjdt(L, tt, sz, 0);
}