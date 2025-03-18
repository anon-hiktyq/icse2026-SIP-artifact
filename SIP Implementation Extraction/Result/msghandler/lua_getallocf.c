#include "lua_getallocf.h"
void lua_getallocfFun(void *p) 
{
    lua_getallocf *pIp = (lua_getallocf*)p;
  lua_Alloc pIp -> f;
  lua_lock(pIp -> L);
  if pIp -> (ud) *ud = G(pIp -> L)->pIp -> ud;
  pIp -> f = G(pIp -> L)->frealloc;
  lua_unlock(pIp -> L);
  *(pIp -> ret) = f;
}