#include "lua_pushlightuserdata.h"
void lua_pushlightuserdataFun(void *p) 
{
    lua_pushlightuserdata *pIp = (lua_pushlightuserdata*)p;
  lua_lock(pIp -> L);
  setpvalue(s2v(pIp -> L->top.pIp -> p), pIp -> p);
  api_incr_top(pIp -> L);
  lua_unlock(pIp -> L);
}