#include "lua_pushboolean.h"
void lua_pushbooleanFun(void *p) 
{
    lua_pushboolean *pIp = (lua_pushboolean*)p;
  lua_lock(pIp -> L);
  if (pIp -> b)
    setbtvalue(s2v(pIp -> L->top.p));
  else
    setbfvalue(s2v(pIp -> L->top.p));
  api_incr_top(pIp -> L);
  lua_unlock(pIp -> L);
}