#include "luaV_modf.h"
void luaV_modfFun(void *p) 
{
    luaV_modf *pIp = (luaV_modf*)p;
  lua_Number r;
  luai_nummod(pIp -> L, pIp -> m, pIp -> n, r);
  *(pIp -> ret) = r;
}