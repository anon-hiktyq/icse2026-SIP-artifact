#include "luaV_modf.h"
void luaV_modfFun(void *p) 
{
    luaV_modf *pIp = (luaV_modf*)p;
  lua_Number pIp -> r;
  luai_nummod(pIp -> L, pIp -> m, pIp -> n, pIp -> r);
  *(pIp -> ret) = r;
}