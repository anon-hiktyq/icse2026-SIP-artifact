#include "luaL_addstring.h"
void luaL_addstringFun(void *p) 
{
    luaL_addstring *pIp = (luaL_addstring*)p;
  {IPCALL(luaL_addlstring,ipluaL_addlstring_0,.pIp->B = pIp->pIp->B,.pIp->s = pIp->pIp->s,.l = strlen(pIp->s));}
}