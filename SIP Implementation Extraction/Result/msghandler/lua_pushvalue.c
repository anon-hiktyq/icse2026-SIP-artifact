#include "lua_pushvalue.h"
void lua_pushvalueFun(void *p) 
{
    lua_pushvalue *pIp = (lua_pushvalue*)p;
  lua_lock(pIp -> L);
  setobj2s(pIp -> L, pIp -> L->top.p, index2value(pIp -> L, pIp -> idx));
  api_incr_top(pIp -> L);
  lua_unlock(pIp -> L);
}