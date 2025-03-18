#include "lua_gettop.h"
void lua_gettopFun(void *p) 
{
    lua_gettop *pIp = (lua_gettop*)p;
  *(pIp -> ret) = cast_int(L->top.p - (L->ci->func.p + 1));
}