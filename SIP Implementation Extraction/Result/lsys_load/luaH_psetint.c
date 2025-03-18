#include "luaH_psetint.h"
void luaH_psetintFun(void *p) 
{
    luaH_psetint *pIp = (luaH_psetint*)p;
  lua_assert(!ikeyinarray(pIp -> t, pIp -> key));
  *(pIp -> ret) = finishnodeset(t, getintfromhash(t, key), val);
}